/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:52:27 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/03 16:57:59 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	help(t_error error)
{
	if (error == ARGC_ERROR)
		printf("Error: Invalid number of arguments.\n\n");
	else if (error == NUMBER_ERROR)
		printf("Error: Arguments must be positive integers.\n\n");
	else if (error == N_PHILOS_ZERO)
		printf("Error: Number of philos cannot be 0.\n\n");
	else if (error == N_TIMES_EAT_ZERO)
		printf("Error: Number of times each philo eat cannot be 0.\n\n");
	printf("\tUsage: ./philo <n_philosophers> <time_to_die> <time_to_eat>");
	printf(" <time_to_sleep> [n_times_each_philosopher_eat]\n");
	printf("\t<> --> obligatory\n\t[] --> optional\n\n");
}

t_bool	is_space(char c)
{
	return ((c == ' ') || (c >= 9 && c <= 13));
}

t_bool	is_sign(char c)
{
	return (c == '+' || c == '-');
}
