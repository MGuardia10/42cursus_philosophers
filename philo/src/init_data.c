/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:12:44 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/29 08:36:42 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/colors.h"
#include "../inc/error.h"

/**
 * The function "memory_allocation" allocates memory for an array of forks and
 * an array of philosophers in a table structure.
 * 
 * @param table A pointer to a structure of type t_table, which contains
 * information about the table and the philosophers.
 * 
 * @return an integer value. If the memory allocation is successful, it returns
 * 0. If there is an error in memory allocation, it returns 1.
 */
static int	memory_allocation(t_table *table)
{
	table->forks = malloc(table->n_philos * sizeof(t_fork));
	if (!table->forks)
		return (1);
	table->philos = malloc(table->n_philos * sizeof(t_philo));
	if (!table->philos)
	{
		free(table->forks);
		return (1);
	}
	return (0);
}

/**
 * The function initializes mutexes for a table and its forks.
 * 
 * @param table A pointer to a structure of type t_table, which contains
 * information about the table and the philosophers.
 * 
 * @return an integer value. If the function is successful, it will return 0. If
 * there is an error, it will return 1.
 */
static int	init_mutexes(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->table_mtx, NULL))
		return (1);
	if (pthread_mutex_init(&table->control_mtx, NULL))
		return (1);
	if (pthread_mutex_init(&table->write_mtx, NULL))
		return (1);
	i = 0;
	while (i < table->n_philos)
	{
		table->forks[i].id = i;
		if (pthread_mutex_init(&table->forks[i].fork_mtx, NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i].fork_mtx);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * The function assigns forks to a philosopher based on their position and
 * whether their ID is even or odd.
 * 
 * @param philo A pointer to a struct representing a philosopher.
 * @param forks An array of t_fork structures representing the available forks.
 * @param philo_pos The position of the philosopher in the table (0-indexed).
 */
static void	assing_forks(t_philo *philo, t_fork *forks, unsigned int philo_pos)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &(forks[philo_pos]);
		philo->second_fork = &(forks[(philo_pos + 1) % philo->table->n_philos]);
	}
	else
	{
		philo->first_fork = &(forks[(philo_pos + 1) % philo->table->n_philos]);
		philo->second_fork = &(forks[philo_pos]);
	}
}

/**
 * The function initializes the philosophers in a dining table by assigning 
 * them unique IDs, initializing their meal counters and last meal times,
 * setting their fullness status to false, and initializing the necessary
 * mutexes and forks.
 * 
 * @param table A pointer to a struct of type t_table, that contains information
 * about the dining table and the philosophers sitting at the table.
 * 
 * @return an integer value.
 */
static int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meal_counter = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].is_full = false;
		table->philos[i].table = table;
		if (pthread_mutex_init(&table->philos[i].philo_mtx, NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->philos[i].philo_mtx);
			return (1);
		}
		assing_forks(&table->philos[i], table->forks, i);
		i++;
	}
	return (0);
}

/**
 * The function initializes data for a table structure, including memory
 * allocation, mutex initialization, and philosophers initialization.
 * 
 * @param table A pointer to a structure of type t_table.
 * 
 * @return an integer value. If memory allocation or initialization of mutexes
 * or philosophers fails, it will return 1. Otherwise, it will return 0.
 */
int	init_data(t_table *table)
{
	if (memory_allocation(table))
		return (printf("%s"MALLOC_ERROR"%s\n", RED, RES), 1);
	if (init_mutexes(table) || init_philos(table))
	{
		free(table->forks);
		free(table->philos);
		return (printf("%s"MUTEX_ERROR"%s\n", RED, RES), 1);
	}
	return (0);
}
