/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:52:27 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/27 22:09:00 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	is_space(char c)
{
	return ((c == ' ') || (c >= 9 && c <= 13));
}

bool	is_sign(char c)
{
	return (c == '+' || c == '-');
}

long	get_time(t_time_format time_format)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (time_format == MILISECONDS)
		return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
	else if (time_format == MICROSECONDS)
		return ((time.tv_sec * 1e6) + time.tv_usec);
	return (42);
}

bool	is_dead(t_philo *philo)
{
	long	dif;
	long	last_meal;

	last_meal = get_long(&philo->philo_mtx, &philo->last_meal_time);
	dif = get_time(MILISECONDS) - last_meal;
	return (dif > philo->table->time_die);
}

void	usleep_mod(long wait_time, t_table *table)
{
	long	t_start;
	long	t_curr;
	long	t_remaining;

	t_start = get_time(MICROSECONDS);
	while ((get_time(MICROSECONDS) - t_start) < wait_time)
	{
		if (is_simulation_finish(table) == true)
			return ;
		t_curr = get_time(MICROSECONDS) - t_start;
		t_remaining = wait_time - t_curr;

		if (t_remaining > 1000)
			usleep(t_remaining / 2);
		else
		{
			while ((get_time(MICROSECONDS) - t_start) < wait_time)
				;
		}
	}
}
