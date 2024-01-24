/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:41:14 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/24 11:14:01 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// ARGC & ARGV errors
# define ARGC_ERROR			"Error: Invalid number of arguments."
# define NUMBER_ERROR		"Error: Arguments must be positive integers."
# define PHILOS_ZERO_ERROR	"Error: Number of philos cannot be 0."
# define N_EAT_ZERO_ERROR	"Error: Number of times each philo eat cannot be 0."
# define MALLOC_ERROR		"Error: Problem allocating memory."
# define MUTEX_ERROR		"Error: Problem creating mutex."
# define THREAD_ERROR		"Error: Problem creating thread"

#endif