/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:35:42 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/27 10:50:26 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * The function ´eating´ is responsible for a philosopher taking two forks,
 * eating, and then releasing the forks. It also updates the number of times the
 * philo has eaten and the last meal time. ´is_full´ flag is converted to true
 * once the philo has reached the maximum number of meals given by the user.
 * 
 * @param philo A pointer to a struct representing a philosopher.
 */
void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork_mtx);
	print_action(TAKING_A_FORK, philo->table, *philo);
	pthread_mutex_lock(&philo->second_fork->fork_mtx);
	print_action(TAKING_A_FORK, philo->table, *philo);
	print_action(EATING, philo->table, *philo);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILISECONDS));
	philo->meal_counter++;
	if (philo->meal_counter == philo->table->n_times_eat)
		philo->is_full = true;
	usleep(philo->table->time_eat * 1e3);
	pthread_mutex_unlock(&philo->first_fork->fork_mtx);
	pthread_mutex_unlock(&philo->second_fork->fork_mtx);
}
