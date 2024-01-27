/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:12:44 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/27 22:27:09 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/colors.h"
#include "../inc/error.h"

static int	init_mutexes(t_table *table)
{
	unsigned int	i;

	pthread_mutex_init(&table->table_mtx, NULL);
	pthread_mutex_init(&table->control_mtx, NULL);
	pthread_mutex_init(&table->write_mtx, NULL);
	table->forks = malloc(table->n_philos * sizeof(t_fork));
	if (!table->forks)
		return (printf("%s"MALLOC_ERROR"%s\n", RED, RES), 1);
	i = 0;
	while (i < table->n_philos)
	{
		table->forks[i].id = i;
		if (pthread_mutex_init(&table->forks[i].fork_mtx, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i].fork_mtx);
			return (printf("%s"MUTEX_ERROR"%s\n", RED, RES), 1);
		}
		i++;
	}
	return (0);
}

void	assing_forks(t_philo *philo, t_fork *forks, unsigned int philo_pos)
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

static int	init_philos(t_table *table)
{
	unsigned int	i;

	table->philos = malloc(table->n_philos * sizeof(t_philo));
	if (!table->philos)
		return (printf("%s"MALLOC_ERROR"%s\n", RED, RES), \
			free(table->forks), 1);
	i = 0;
	while (i < table->n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meal_counter = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].is_full = false;
		table->philos[i].table = table;
		pthread_mutex_init(&table->philos[i].philo_mtx, NULL);
		assing_forks(&table->philos[i], table->forks, i);
		i++;
	}
	return (0);
}

int	init_data(t_table *table)
{
	if (init_mutexes(table))
		return (1);
	if (init_philos(table))
		return (1);
	return (0);
}
