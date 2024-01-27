/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:50:33 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/27 22:26:03 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * The function ´safe_exit´ is responsible for cleaning up and freeing the
 * memory used by the program and its associated mutexes.
 * 
 * @param table A pointer to a structure of type t_table, which contains
 * information about the table and the philosophers sitting at the table.
 */
void	safe_exit(t_table *table)
{
	unsigned int	i;

	pthread_mutex_destroy(&table->table_mtx);
	pthread_mutex_destroy(&table->write_mtx);
	pthread_mutex_destroy(&table->control_mtx);
	i = -1;
	while (++i < table->n_philos)
	{
		pthread_mutex_destroy(&table->forks[i].fork_mtx);
		pthread_mutex_destroy(&table->philos[i].philo_mtx);
	}
	free(table->philos);
	free(table->forks);
}
