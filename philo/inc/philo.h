/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:27:08 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/13 20:14:30 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <string.h>	// memset
# include <unistd.h>	// write, usleep
# include <sys/time.h>	// gettimeofday
# include <pthread.h>	// threads & mutex

// typedefs
typedef enum e_bool		t_bool;
typedef enum e_error	t_error;
typedef struct s_all	t_all;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;

// enums
enum e_bool
{
	false,
	true
};

enum e_error
{
	ARGC_ERROR,
	NUMBER_ERROR,
	N_PHILOS_ZERO,
	N_TIMES_EAT_ZERO,
};

// structs
struct s_fork
{
	unsigned int	id;
	pthread_mutex_t	mutex;
};

struct s_philo
{
	unsigned int	id;
	size_t			meal_counter;
	size_t			last_meal_time;
	t_bool			is_full;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	t_all			*data;
};

struct s_all
{
	size_t	n_philos;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	long	n_times_eat; // if -1 --> no n_times_eat
	size_t	start_sim;
	size_t	end_sim; // simulation finish when a philo dies or everyone is full.
	t_philo	*philos;
	t_fork	*forks;
};

// parsing arguments
int		args_parsing(t_all *data, char **argv);

// init_data
int		init_data(t_all *data);

// print funcitons
void	help(t_error error);
void	print_info(t_all data);

// utils
t_bool	is_space(char c);
t_bool	is_sign(char c);

#endif