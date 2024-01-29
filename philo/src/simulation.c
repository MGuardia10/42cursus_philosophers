/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:21:54 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/29 09:11:03 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/error.h"
#include "../inc/colors.h"

/**
 * The function represents the routine when there is only one philosopher. In
 * this case there is only one fork in the table, so the only thing the philo
 * can do is taking the fork and wait wait to die from starvation.
 * 
 * @param philo A pointer to a structure representing a philosopher.
 * 
 * @return a NULL pointer.
 */
static void	*one_philo_routine(t_philo *philo)
{
	print_action(TAKING_A_FORK, philo->table, *philo);
	while (is_simulation_finish(philo->table) == false)
		;
	return (NULL);
}

/**
 * The function "philo_routine" is a thread function that represents the routine
 * of a philosopher in a dining philosophers problem simulation.
 * 
 * @param data The `data` parameter is a void pointer that is cast to a
 * `t_philo` struct pointer. It represents the data associated with a
 * philosopher.
 * 
 * @return a `NULL` value.
 */
static void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	philo->last_meal_time = get_time(MILISECONDS);
	increment_n_philos(philo->table);
	if (philo->table->n_philos == 1)
		return (one_philo_routine(philo));
	make_simulation_fair(philo);
	while (is_simulation_finish(philo->table) == false)
	{
		eating(philo);
		if (philo->is_full == true)
			break ;
		print_action(SLEEPING, philo->table, *philo);
		usleep_mod(philo->table->time_sleep * 1e3, philo->table);
		print_action(THINKING, philo->table, *philo);
		thinking(philo);
	}
	return (NULL);
}

/**
 * The supervisor_routine function checks if any philosophers have died and ends
 * the simulation if necessary.
 * 
 * @param data The "data" parameter is a void pointer that is cast to a t_table
 * pointer. It is used to pass a pointer to a t_table struct to the
 * supervisor_routine function.
 * 
 * @return a NULL pointer.
 */
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

/**
 * The function starts a simulation by creating threads for the supervisor and
 * philosophers, and then waits for all threads to finish before ending the
 * simulation.
 * 
 * @param table The parameter "table" is a pointer to a struct of type 
 * "t_table". This struct likely contains information about the simulation, 
 * such as the number of philosophers, the start time, and control variables
 * for starting and ending the simulation.
 * 
 * @return an integer value. If the simulation is started successfully and all
 * threads are created without any errors, the function will return 0. If there
 * is an error in creating the threads, the function will return 1.
 */
int	start_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	if (pthread_create(&table->supervisor, NULL, supervisor_routine, table))
		return (printf("%s"THREAD_ERROR"%s\n", RED, RES), 1);
	while (i < table->n_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine, \
													&table->philos[i]))
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
