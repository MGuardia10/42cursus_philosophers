/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:41:14 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/27 09:59:24 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
* Arguments errors
*/
# define ARGC_ERROR			"Error: Invalid number of arguments."
# define NUMBER_ERROR		"Error: Arguments must be positive integers."
# define PHILOS_ZERO_ERROR	"Error: Number of philos cannot be 0."
# define N_EAT_ZERO_ERROR	"Error: Number of times each philo eat cannot be 0."
# define INT_MAX_ERROR		"Error: Numbers can´t exceed INT_MAX value."
/*
* Memory errors
*/
# define MALLOC_ERROR		"Error: Problem allocating memory."

/*
* Threads & mutexes errors
*/
# define MUTEX_ERROR		"Error: Problem creating mutex."
# define THREAD_ERROR		"Error: Problem creating thread."

#endif