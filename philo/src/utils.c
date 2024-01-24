/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:52:27 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/23 10:04:13 by mguardia         ###   ########.fr       */
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

size_t get_time(t_time_format time_format)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	if (time_format == MICROSECONDS)
		return ((time.tv_sec * 1e6) + time.tv_usec);
	else if (time_format == MILISECONDS)
		return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
	else if (time_format == SECONDS)
		return (time.tv_sec + (time.tv_usec / 1e6));
	return (1);
}