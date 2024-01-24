/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:10:50 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/24 11:04:11 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	wait_all_threads(t_all *data)
{
	while (get_bool(data->start_mtx, &data->start_sim) == false)
		;
}

bool	all_philos_running(t_mtx mutex, t_all *table)
{
	bool	all_running;

	pthread_mutex_lock(&mutex);
	// printf("philos running: %zu\n", table->n_philos_running);
	// printf("philos total: %zu\n", table->n_philos);
	if (table->n_philos_running == table->n_philos)
		all_running = true;
	else
		all_running = false;
	pthread_mutex_unlock(&mutex);
	return (all_running);
}

bool	is_simulation_finish(t_all *data)
{
	return (get_bool(data->table_mtx, &data->end_sim));
}

