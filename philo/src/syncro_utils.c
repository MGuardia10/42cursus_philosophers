/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:10:50 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/25 19:55:12 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_all_threads(t_all *data)
{
	while (get_bool(data->control_mtx, &data->start_sim) == false)
		;
}

bool	all_philos_running(t_mtx mutex, t_all *table)
{
	size_t	philos_running;

	pthread_mutex_lock(&mutex);
	philos_running = table->all_philos_running;
	pthread_mutex_unlock(&mutex);
	return (philos_running);
}

bool	is_simulation_finish(t_all *data)
{
	return (get_bool(data->control_mtx, &data->end_sim));
}
