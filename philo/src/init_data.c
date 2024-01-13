/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:12:44 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/13 20:13:53 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/colors.h"

static int	init_mutex(t_all *data)
{
	unsigned int	i;

	data->forks = malloc(data->n_philos * sizeof(t_fork));
	if (!data->forks)
		return (printf("%sError: Problem allocating memory.%s\n", RED, RES), 1);
	i = 0;
	while (i < data->n_philos)
	{
		data->forks[i].id = i;
		if (pthread_mutex_init(&data->forks[i].mutex, NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i].mutex);
			return (printf("%sError: Problem with mutex.%s\n", RED, RES), 1);
		}
		// printf("fork with id: %d allocated okay\n", data->forks[i].id);
		i++;
	}
	return (0);
}

static void	*routine(void *data)
{
	(void)data;
	return NULL;
}

static int	init_philos(t_all *data)
{
	unsigned int	i;
	data->philos = malloc(data->n_philos * sizeof(t_philo));
	if (!data->philos)
		return (printf("%sError: Problem allocating memory.%s\n", RED, RES), \
			free(data->forks), 1);
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		// data->philos[i].meal_counter = 0;
		// data->philos[i].last_meal_time = 0;
		// data->philos[i].is_full = false;
		if (pthread_create(&data->philos[i].thread_id, NULL, routine, data))
			return (printf("%sError: Problem with threads.%s\n", RED, RES), 1);
		i++;
	}
	return (0);
}

int	init_data(t_all *data)
{
	// iniciar los forks, un mutex por cada fork
	if (init_mutex(data))
		return (1);
	// iniciar datos del philo.
	if (init_philos(data))
		return (1);
	// asignar tenedores a cada philo
	// assing_forks();
	return (0);
}