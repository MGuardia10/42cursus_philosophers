/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:35:42 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/28 13:36:23 by mguardia         ###   ########.fr       */
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
	usleep_mod(philo->table->time_eat * 1000, philo->table);
	pthread_mutex_unlock(&philo->first_fork->fork_mtx);
	pthread_mutex_unlock(&philo->second_fork->fork_mtx);
}

/**
 * The ´thinking´ function calculates the time a philosopher should spend
 * thinking based on the eating and sleeping times, and then sleeps for that
 * amount of time.
 * 
 * @param philo A pointer to a struct representing a philosopher.
 * 
 * @return If the number of philosophers is even, the function returns without
 * doing anything.
 */
void	thinking(t_philo *philo)
{
	long	t_think;

	if (philo->table->n_philos % 2 == 0)
		return ;
	t_think = (philo->table->time_eat * 2 - philo->table->time_sleep) * 1e3;
	if (t_think < 0)
		t_think = 0;
	usleep_mod(t_think * 0.5, philo->table);
}
