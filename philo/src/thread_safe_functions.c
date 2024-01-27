/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 06:53:42 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/27 09:49:05 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


/**
 * The function `get_bool` reads the value of a boolean variable protected by a
 * mutex.
 * 
 * @param mutex The parameter "mutex" is of type "t_mtx", which is likely a 
 * typedef for a mutex data structure. It is used to synchronize access to the
 * shared variable "value" to prevent concurrent access and ensure thread
 * safety.
 * @param value A pointer to a boolean variable that will update a local 
 * variable with the value read from the mutex-protected variable.
 * 
 * @return the value of the variable "read_value".
 */
bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	read_value;

	pthread_mutex_lock(mutex);
	read_value = *value;
	pthread_mutex_unlock(mutex);
	return (read_value);
}

/**
 * The function `get_long` reads the value stored in a long variable protected
 * by a mutex and returns it.
 * 
 * @param mutex The parameter "mutex" is of type "t_mtx", which is likely a 
 * typedef for a mutex data structure. It is used to synchronize access to the
 * shared variable "value" to prevent concurrent access and ensure thread
 * safety.
 * @param value A pointer to a long integer variable that holds the value to be
 * read.
 * 
 * @return the value of the variable `read_value`.
 */
long	get_long(t_mtx *mutex, long *value)
{
	long	read_value;

	pthread_mutex_lock(mutex);
	read_value = *value;
	pthread_mutex_unlock(mutex);
	return (read_value);
}

/**
 * The function `set_bool` sets the value of a boolean property while ensuring
 * thread safety using a mutex.
 * 
 * @param mutex The parameter "mutex" is of type "t_mtx", which is likely a 
 * typedef for a mutex data structure. It is used to synchronize access to the
 * shared variable "value" to prevent concurrent access and ensure thread
 * safety.
 * @param property A pointer to a boolean variable that we want to set the value
 * of.
 * @param value The value parameter is the new value that you want to assign to
 * the property.
 */
void	set_bool(t_mtx *mutex, bool *property, bool value)
{
	pthread_mutex_lock(mutex);
	*property = value;
	pthread_mutex_unlock(mutex);
}

/**
 * The function `set_long` sets the value of a long property while ensuring
 * thread safety using a mutex.
 * 
 * @param mutex The parameter "mutex" is of type "t_mtx", which is likely a 
 * typedef for a mutex data structure. It is used to synchronize access to the
 * shared variable "value" to prevent concurrent access and ensure thread
 * safety.
 * @param property A pointer to a long variable that we want to set the value
 * of.
 * @param value The value parameter is the new value that you want to assign to
 * the property.
 */
void	set_long(t_mtx *mutex, long *property, long value)
{
	pthread_mutex_lock(mutex);
	*property = value;
	pthread_mutex_unlock(mutex);
}

/**
 * The function increments the number of philosophers currently running and
 * checks if all philosophers are running.
 * 
 * @param data A pointer to a struct of type t_all, which contains various data
 * related to the program.
 */
void	increment_n_philos(t_table *table)
{
	pthread_mutex_lock(&table->table_mtx);
	table->n_philos_running += 1;
	if (table->n_philos_running == table->n_philos)
		set_bool(&table->control_mtx, &table->all_philos_running, true);
	pthread_mutex_unlock(&table->table_mtx);
}
