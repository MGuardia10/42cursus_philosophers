/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:21:54 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/27 10:37:08 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/error.h"
#include "../inc/colors.h"

void	*one_philo_routine(t_philo *philo)
{
	while (is_simulation_finish(philo->table) == false)
		;
	return (NULL);
}

static void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// esperar que todos los hilos sean creados
	wait_all_threads(philo->table);
	philo->last_meal_time = get_time(MILISECONDS);
	increment_n_philos(philo->table);
	// Si solo hay un philo:
	if (philo->table->n_philos == 1)
		return (one_philo_routine(philo));
	// caso contrario: comenzar bucle
	while (is_simulation_finish(philo->table) == false)
	{
		// eating
		eating(philo);
		// Si esta lleno, terminar hilo
		if (philo->is_full == true)
			break ;
		// sleeping after eating
		print_action(SLEEPING, philo->table, *philo);
		usleep(philo->table->time_sleep * 1e3);
		// thinking
		print_action(THINKING, philo->table, *philo);
	}
	return (NULL);
}

static void	*supervisor_routine(void *data)
{
	t_table			*table;
	unsigned int	i;

	table = (t_table *)data;
	while (all_philos_running(&table->control_mtx, table) == false)
		;
	while (is_simulation_finish(table) == false)
	{
		i = -1;
		while (++i < table->n_philos && is_simulation_finish(table) == false)
		{
			if (is_dead(&table->philos[i]) == true)
			{
				print_action(DEAD, table, table->philos[i]);
				set_bool(&table->control_mtx, &table->end_sim, true);
			}
		}
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	if (pthread_create(&table->supervisor, NULL, supervisor_routine, table) != 0)
		return (printf("%s"THREAD_ERROR"%s\n", RED, RES), 1);
	while (i < table->n_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine, \
														&table->philos[i]) != 0)
			return (printf("%s"THREAD_ERROR"%s\n", RED, RES), 1);
		i++;
	}
	table->start_time = get_time(MILISECONDS);
	set_bool(&table->control_mtx, &table->start_sim, true);
	i = -1;
	while (++i < table->n_philos)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->control_mtx, &table->end_sim, true);
	pthread_join(table->supervisor, NULL);
	return (0);
}
