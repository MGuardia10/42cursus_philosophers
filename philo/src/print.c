/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:54:11 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/28 13:47:22 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/colors.h"
#include "../inc/error.h"

/**
 * The function ´help´ prints an error message and usage instructions for a
 * program when there is a problem with the arguments.
 * 
 * @param error The `error` parameter is a string that represents an error
 * message. It is used to display the error message to the user.
 */
void	help(char *error)
{
	printf("%s%s%s\n\n", BRED, error, RES);
	printf("\t%sUsage: ./philo <n_philos> <time_to_die> <time_to_eat>", BMAG);
	printf(" <time_to_sleep> [n_times_each_philosopher_eat]\n");
	printf("\t<> --> obligatory\n\t[] --> optional\n\n%s", RES);
}

/**
 * The function "print_info" prints out information about the conditions of the
 * simulation based on the user input.
 * 
 * @param table The `table` parameter is of type `t_table`, which is a struct
 * that contains information about the simulation.
 */
void	print_info(t_table table)
{
	printf("\n%s********************* INPUT *********************\n|\n", BBLU);
	printf("|-->  %stotal Philos 🧙   =  %zu philos%s\n", \
									GRN, table.n_philos, BBLU);
	printf("|-->  %stime to die 💀    =  %zu ms%s\n", \
									RED, table.time_die, BBLU);
	printf("|-->  %stime to eat 🍝    =  %zu ms%s\n", \
									YEL, table.time_eat, BBLU);
	printf("|-->  %stime to sleep 😴  =  %zu ms%s\n", \
									CYN, table.time_sleep, BBLU);
	if (table.n_times_eat == -1)
		printf("|-->  %snumber meals 🥣   =  not specified%s\n", MAG, BBLU);
	else
		printf("|-->  %snumber meals 🥣   =  %zu meals%s\n", \
									MAG, table.n_times_eat, BBLU);
	printf("\n\n           %s-- %s STARTING SIMULATION %s%s --%s\n\n", \
									BGRN, GRNB, RES, BGRN, RES);
}

/**
 * The function `print_action` prints the action of a philosopher along with the
 * current time.
 * 
 * @param action The "action" parameter is of type "t_action" and represents the
 * action that the philosopher is performing.
 * @param table A pointer to a structure representing the dining table.
 * @param philo The `philo` parameter is of type `t_philo` and represents a
 * philosopher in the dining philosophers problem.
 */
void	print_action(t_action action, t_table *table, t_philo philo)
{
	size_t	start_time;

	start_time = table->start_time;
	pthread_mutex_lock(&table->write_mtx);
	if (action == DEAD && is_simulation_finish(table) == false)
		printf("%-6zu %d died\n", get_time(MILISECONDS) - start_time, philo.id);
	else if (action == EATING && is_simulation_finish(table) == false)
		printf("%-6zu %d is eating\n", get_time(MILISECONDS) - start_time, \
																	philo.id);
	else if (action == SLEEPING && is_simulation_finish(table) == false)
		printf("%-6zu %d is sleeping\n", get_time(MILISECONDS) - start_time, \
																	philo.id);
	else if (action == THINKING && is_simulation_finish(table) == false)
		printf("%-6zu %d is thinking\n", get_time(MILISECONDS) - start_time, \
																	philo.id);
	else if (action == TAKING_A_FORK && is_simulation_finish(table) == false)
		printf("%-6zu %d has taken a fork\n", \
						get_time(MILISECONDS) - start_time, philo.id);
	pthread_mutex_unlock(&table->write_mtx);
}
