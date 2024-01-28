/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:52:27 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/28 13:52:09 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * The function checks if a character is a space or a whitespace character.
 * 
 * @param c The parameter "c" is a character that we want to check if it is a
 * space or not.
 * 
 * @return a boolean value, either true or false.
 */
bool	is_space(char c)
{
	return ((c == ' ') || (c >= 9 && c <= 13));
}

/**
 * The function checks if a character is a plus or minus sign.
 * 
 * @param c The parameter "c" is a character that is being checked to see if it
 * is a plus sign (+) or a minus sign (-).
 * 
 * @return a boolean value, which indicates whether the character passed as an
 * argument is a plus sign (+) or a minus sign (-).
 */
bool	is_sign(char c)
{
	return (c == '+' || c == '-');
}

/**
 * The function "get_time" returns the current time in either milliseconds or
 * microseconds.
 * 
 * @param time_format The parameter "time_format" is an enumeration type called
 * "t_time_format". It is used to specify the desired format for the time value
 * returned by the function "get_time". The possible values for "time_format"
 * are "MILISECONDS" and "MICROSECONDS".
 * 
 * @return the current time in the specified format. If the time format is
 * neither MILISECONDS nor MICROSECONDS.
 */
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

/**
 * The function checks if a philosopher is dead based on the time since their
 * last meal.
 * 
 * @param philo A pointer to a structure representing a philosopher.
 * 
 * @return a boolean value, which indicates if the philosopher is dead or not.
 */
bool	is_dead(t_philo *philo)
{
	long	dif;
	long	last_meal;

	last_meal = get_long(&philo->philo_mtx, &philo->last_meal_time);
	dif = get_time(MILISECONDS) - last_meal;
	return (dif > philo->table->time_die);
}

/**
 * The function usleep_mod is used to pause the program execution for a
 * specified amount of time, taking into account the remaining time and checking
 * if the simulation has finished.
 * 
 * @param wait_time The wait_time parameter is the amount of time in
 * microseconds that the function should wait before returning.
 * @param table A pointer to a structure or object of type t_table.
 * 
 * @return The function does not explicitly return a value. Only returns if at
 * any time the flag that marks the end of the simulation is activated.
 */
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
