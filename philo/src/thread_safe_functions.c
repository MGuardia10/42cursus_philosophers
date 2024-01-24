/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 06:53:42 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/24 11:04:28 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

// Getters
bool	get_bool(t_mtx mutex, bool *value)
{
	bool	read_value;

	pthread_mutex_lock(&mutex);
	read_value = *value;
	pthread_mutex_unlock(&mutex);
	return (read_value);
}

size_t	get_size_t(t_mtx mutex, size_t *value)
{
	size_t	read_value;

	pthread_mutex_lock(&mutex);
	read_value = *value;
	pthread_mutex_unlock(&mutex);
	return (read_value);
}
// Setters
void	set_bool(t_mtx mutex, bool *property, bool value)
{
	pthread_mutex_lock(&mutex);
	*property = value;
	pthread_mutex_unlock(&mutex);
}

void	set_size_t(t_mtx mutex, size_t *property, size_t value)
{
	pthread_mutex_lock(&mutex);
	*property = value;
	pthread_mutex_unlock(&mutex);
}
