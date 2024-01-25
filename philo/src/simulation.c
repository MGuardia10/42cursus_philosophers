/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:21:54 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/25 19:55:51 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/error.h"
#include "../inc/colors.h"

bool	is_dead(t_philo philo)
{
	size_t	dif;

	dif = get_time(MILISECONDS) - philo.last_meal_time;
	if (dif > philo.data->time_die)
		return (true);
	return (false);
}

void	*one_philo_routine(t_philo *philo)
{
	while (is_simulation_finish(philo->data) == false)
		;
	return (NULL);
}

static void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// esperar que todos los hilos sean creados
	wait_all_threads(philo->data);
	philo->last_meal_time = get_time(MILISECONDS);
	increment_n_philos(philo->data);
	// Si solo hay un philo:
	if (philo->data->n_philos == 1)
		return (one_philo_routine(philo));
	// caso contrario: comenzar bucle
	while (is_simulation_finish(philo->data) == false)
	{
		// TODO
		usleep(100);
	}
	return (NULL);
}

void	*supervisor_routine(void *data)
{
	t_all			*table;
	unsigned int	i;

	table = (t_all *)data;
	while (all_philos_running(table->control_mtx, table) == false)
		;
	while (is_simulation_finish(table) == false)
	{
		i = -1;
		while (++i < table->n_philos && is_simulation_finish(table) == false)
		{
			if (is_dead(table->philos[i]) == true)
			{
				set_bool(table->control_mtx, &table->end_sim, true);
				print_action(DEAD, table, table->philos[i]);
			}
		}
	}
	return (NULL);
}

int	start_simulation(t_all *data)
{
	unsigned int	i;

	i = 0;
	if (pthread_create(&data->supervisor, NULL, supervisor_routine, data) != 0)
		return (printf("%s"THREAD_ERROR"%s\n", RED, RES), 1);
	while (i < data->n_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, philo_routine, \
														&data->philos[i]) != 0)
			return (printf("%s"THREAD_ERROR"%s\n", RED, RES), 1);
		i++;
	}
	data->start_time = get_time(MILISECONDS);
	set_bool(data->control_mtx, &data->start_sim, true);
	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->philos[i].thread_id, NULL);
	set_bool(data->control_mtx, &data->end_sim, true);
	pthread_join(data->supervisor, NULL);
	return (0);
}
