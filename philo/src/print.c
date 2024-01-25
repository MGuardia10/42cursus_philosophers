/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:54:11 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/25 19:59:08 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/colors.h"
#include "../inc/error.h"

void	help(char *error)
{
	printf("%s%s%s\n\n", BRED, error, RES);
	printf("\t%sUsage: ./philo <n_philos> <time_to_die> <time_to_eat>", BMAG);
	printf(" <time_to_sleep> [n_times_each_philosopher_eat]\n");
	printf("\t<> --> obligatory\n\t[] --> optional\n\n%s", RES);
}

void	print_info(t_all data)
{
	printf("\n%s********************* INPUT *********************\n|\n", BBLU);
	printf("|-->  %stotal Philos 🧙   =  %zu philos%s\n", \
									GRN, data.n_philos, BBLU);
	printf("|-->  %stime to die 💀    =  %zu ms%s\n", \
									RED, data.time_die, BBLU);
	printf("|-->  %stime to eat 🍝    =  %zu ms%s\n", \
									YEL, data.time_eat, BBLU);
	printf("|-->  %stime to sleep 😴  =  %zu ms%s\n", \
									CYN, data.time_sleep, BBLU);
	if (data.n_times_eat == -1)
		printf("|-->  %snumber meals 🥣   =  not specified%s\n", MAG, BBLU);
	else
		printf("|-->  %snumber meals 🥣   =  %zu meals%s\n", \
									MAG, data.n_times_eat, BBLU);
	printf("\n\n           %s-- %s STARTING SIMULATION %s%s --%s\n\n", \
									BGRN, GRNB, RES, BGRN, RES);
}

void	print_action(t_action action, t_all *table, t_philo philo)
{
	size_t	start_time;

	start_time = table->start_time;
	pthread_mutex_lock(&table->write_mtx);
	if (action == DEAD)
		printf("%-6zu %d died\n", get_time(MILISECONDS) - start_time, philo.id);
	else if (action == EATING)
		printf("%-6zu %d is eating\n", get_time(MILISECONDS) - start_time, \
																	philo.id);
	else if (action == SLEEPING)
		printf("%-6zu %d is sleeping\n", get_time(MILISECONDS) - start_time, \
																	philo.id);
	else if (action == THINKING)
		printf("%-6zu %d is thinking\n", get_time(MILISECONDS) - start_time, \
																	philo.id);
	else if (action == TWO_FORKS)
		printf("%-6zu %d has taken a fork\n", get_time(MILISECONDS) - start_time, philo.id);
	pthread_mutex_unlock(&table->write_mtx);
}

void	print_debug(t_mtx *mutex, char *str)
{
	pthread_mutex_lock(mutex);
	printf("%s\n", str);
	pthread_mutex_unlock(mutex);
}
