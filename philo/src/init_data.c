/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:12:44 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/25 19:54:49 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/colors.h"
#include "../inc/error.h"

static int	init_mutexes(t_all *data)
{
	unsigned int	i;

	pthread_mutex_init(&data->write_mtx, NULL);
	pthread_mutex_init(&data->table_mtx, NULL);
	pthread_mutex_init(&data->control_mtx, NULL);
	data->forks = malloc(data->n_philos * sizeof(t_fork));
	if (!data->forks)
		return (printf("%s"MALLOC_ERROR"%s\n", RED, RES), 1);
	i = 0;
	while (i < data->n_philos)
	{
		data->forks[i].id = i;
		if (pthread_mutex_init(&data->forks[i].fork_mtx, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i].fork_mtx);
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
		philo->second_fork = &(forks[(philo_pos + 1) % philo->data->n_philos]);
	}
	else
	{
		philo->first_fork = &(forks[(philo_pos + 1) % philo->data->n_philos]);
		philo->second_fork = &(forks[philo_pos]);
	}
	// printf("philo[%d] first fork --> fork [%d]\n", philo->id, philo->first_fork->id);
	// printf("philo[%d] second fork --> fork [%d]\n\n", philo->id, philo->second_fork->id);
}

static int	init_philos(t_all *data)
{
	unsigned int	i;

	data->philos = malloc(data->n_philos * sizeof(t_philo));
	if (!data->philos)
		return (printf("%s"MALLOC_ERROR"%s\n", RED, RES), \
			free(data->forks), 1);
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meal_counter = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].is_full = false;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].philo_mtx, NULL);
		assing_forks(&data->philos[i], data->forks, i);
		i++;
	}
	return (0);
}

int	init_data(t_all *data)
{
	if (init_mutexes(data))
		return (1);
	if (init_philos(data))
		return (1);
	return (0);
}
