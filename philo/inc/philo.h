/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:27:08 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/25 19:53:00 by mguardia         ###   ########.fr       */
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
# include <stdbool.h>

/* Typedefs */
typedef enum e_time_format	t_time_format;
typedef enum e_action		t_action;
typedef struct s_all		t_all;
typedef struct s_fork		t_fork;
typedef struct s_philo		t_philo;
typedef pthread_mutex_t		t_mtx;

/* Enums */
enum e_time_format
{
	MILISECONDS,
	MICROSECONDS,
	SECONDS
};

enum e_action
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
	TWO_FORKS
};

/* Structs */
struct s_fork
{
	unsigned int	id;
	t_mtx			fork_mtx;
};

struct s_philo
{
	unsigned int	id;
	size_t			meal_counter;
	size_t			last_meal_time;
	bool			is_full;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	t_mtx			philo_mtx;
	t_all			*data;
};

struct s_all
{
	size_t		n_philos;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	long		n_times_eat; // if -1 --> no n_times_eat

	size_t		n_philos_running;
	bool		all_philos_running;
	size_t		start_time;
	
	bool		start_sim;
	bool		end_sim; // simulation finish when a philo dies or all full.
	
	t_philo		*philos;
	t_fork		*forks;
	
	pthread_t	supervisor;

	t_mtx		table_mtx;
	t_mtx		write_mtx;
	t_mtx		control_mtx;
};

/* parsing arguments */
int		args_parsing(t_all *data, char **argv);

/* Init data */
int		init_data(t_all *data);

/* Simulation */
int		start_simulation(t_all *data);

/* getters y setters */
bool	get_bool(t_mtx mutex, bool *value);
size_t	get_size_t(t_mtx mutex, size_t	*value);
void	set_bool(t_mtx mutex, bool *property, bool value);
void	set_size_t(t_mtx mutex, size_t *property, size_t value);
void	increment_n_philos(t_all *data);
/* Print functions */
void	help(char *error);
void	print_info(t_all data);
void	print_action(t_action action, t_all *table, t_philo philo);

/* Syncro utils */
void	wait_all_threads(t_all *data);
bool	all_philos_running(t_mtx mutex, t_all *table);
bool	is_simulation_finish(t_all *data);

/* Utils */
bool	is_space(char c);
bool	is_sign(char c);
size_t	get_time(t_time_format time_format);

/* Debug */
void	print_debug(t_mtx *mutex, char *str);

#endif