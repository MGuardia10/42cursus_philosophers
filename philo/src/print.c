/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:54:11 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/13 18:51:36 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/colors.h"

void	help(t_error error)
{
	if (error == ARGC_ERROR)
		printf("%sError: Invalid number of arguments.%s\n\n", BRED, RES);
	else if (error == NUMBER_ERROR)
		printf("%sError: Arguments must be positive integers.%s\n\n", \
										BRED, RES);
	else if (error == N_PHILOS_ZERO)
		printf("%sError: Number of philos cannot be 0.%s\n\n", BRED, RES);
	else if (error == N_TIMES_EAT_ZERO)
		printf("%sError: Number of times each philo eat cannot be 0.%s\n\n", \
										BRED, RES);
	printf("\t%sUsage: ./philo <n_philosophers> <time_to_die> <time_to_eat>", \
										BMAG);
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
