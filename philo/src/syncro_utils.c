/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:10:50 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/29 08:45:08 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * The function ´wait_all_threads´ it´s a wrap of the function ´get_bool´ to
 * read the value of the flag that marks the start of the simulation. The only
 * goal of this function is to make the code more readable.
 * 
 * @param table The parameter "table" is of type "t_table", which is a
 * user-defined data structure that includes all the info about the table where
 * the philos are seated.
 */
void	wait_all_threads(t_table *table)
{
	while (get_bool(&table->control_mtx, &table->start_sim) == false)
		;
}

/**
 * The function ´all_philos_running´ checks if all philosophers are currently
 * running. it´s a wrap of the function ´get_bool´ to read the value of the flag
 * that marks the start of the supervisor thread. The only goal of this function
 * is to make the code more readable.
 * 
 * @param mutex A pointer to a mutex object.
 * @param table The `table` parameter is a pointer to a `t_table` struct.
 * 
 * @return the value of the boolean variable "table->all_philos_running".
 */
bool	all_philos_running(t_mtx *mutex, t_table *table)
{
	return (get_bool(mutex, &table->all_philos_running));
}

/**
 * The function ´is_simulation_finish´ checks if the simulation has finished by
 * returning the value of a boolean variable "end_sim". Again, this functions
 * it´s a wrap of the function ´get_bool´ to read the value of the flag
 * that marks the end of the simulation. The only goal of this function
 * is to make the code more readable.
 * 
 * @param table A pointer to a structure of type t_table.
 * 
 * @return a boolean value.
 */
bool	is_simulation_finish(t_table *table)
{
	return (get_bool(&table->control_mtx, &table->end_sim));
}

/**
 * The function "make_simulation_fair" ensures that the simulation is fair by
 * introducing a delay for even-numbered philosophers in tables with an
 * even number of philosophers, and allowing odd-numbered philosophers to
 * continue thinking in tables with an odd number of philosophers.
 * 
 * @param philo A pointer to a structure representing a philosopher in a dining
 * philosophers simulation.
 */
void	make_simulation_fair(t_philo *philo)
{
	if (philo->table->n_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep_mod(1e3, philo->table);
	}
	else
	{
		if (philo->id % 2 == 1)
			thinking(philo);
	}
}
