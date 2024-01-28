/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:27:08 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/28 12:27:06 by mguardia         ###   ########.fr       */
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
# include <stdbool.h>	// true or false
# include <limits.h>	// INT_MAX

/* Typedefs */
typedef enum e_time_format	t_time_format;
typedef enum e_type			t_type;
typedef enum e_action		t_action;
typedef struct s_table		t_table;
typedef struct s_fork		t_fork;
typedef struct s_philo		t_philo;
typedef pthread_mutex_t		t_mtx;

/* Enums */
enum e_time_format
{
	MILISECONDS,
	MICROSECONDS
};

enum e_type
{
	LONG,
	BOOL
};

enum e_action
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
	TAKING_A_FORK
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
	long			meal_counter;
	long			last_meal_time;
	bool			is_full;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	t_mtx			philo_mtx;
	t_table			*table;
};

struct s_table
{
	long		n_philos;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		n_times_eat;
	long		n_philos_running;
	bool		all_philos_running;
	long		start_time;
	bool		start_sim;
	bool		end_sim;
	t_philo		*philos;
	t_fork		*forks;
	pthread_t	supervisor;
	t_mtx		table_mtx;
	t_mtx		write_mtx;
	t_mtx		control_mtx;
};

/* parsing arguments */
int		args_parsing(t_table *table, char **argv);

/* Init data */
int		init_data(t_table *table);

/* Simulation */
int		start_simulation(t_table *table);

/* Actions */
void	eating(t_philo *philo);
void	thinking(t_philo *philo);

/* getters y setters */
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long	*value);
void	set_bool(t_mtx *mutex, bool *property, bool value);
void	set_long(t_mtx *mutex, long *property, long value);
void	increment_n_philos(t_table *table);

/* Print functions */
void	help(char *error);
void	print_info(t_table table);
void	print_action(t_action action, t_table *table, t_philo philo);

/* Syncro utils */
void	wait_all_threads(t_table *table);
bool	all_philos_running(t_mtx *mutex, t_table *table);
bool	is_simulation_finish(t_table *table);
void	make_simulation_fair(t_philo *philo);

/* Utils */
bool	is_space(char c);
bool	is_sign(char c);
long	get_time(t_time_format time_format);
bool	is_dead(t_philo *philo);
void	usleep_mod(long wait_time, t_table *table);

/* Exit */
void	safe_exit(t_table *table);

/* Debug */
void	print_debug(t_mtx *mutex, char *str);

#endif