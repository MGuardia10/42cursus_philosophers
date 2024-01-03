/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:27:08 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/03 16:26:51 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <string.h>	// memset
# include <unistd.h>	// write, usleep
# include <sys/time.h>	// gettimeofday
# include <pthread.h>	// threads

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef enum e_error
{
	ARGC_ERROR,
	NUMBER_ERROR,
	N_PHILOS_ZERO,
	N_TIMES_EAT_ZERO,
}	t_error;

typedef struct s_all
{
	size_t	n_philos;
	size_t	n_forks;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	n_times_eat;
}	t_all;

// init_data
t_bool	init_data(t_all *data, char **argv);

// utils
void	help(t_error error);
t_bool	is_space(char c);
t_bool	is_sign(char c);

#endif