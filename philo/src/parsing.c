/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:54:06 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/27 10:45:30 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/error.h"

/**
 * The function `ft_atol_strict` converts a string to a long integer, strictly
 * checking for valid characters and range limits.
 * 
 * @param nbr A pointer to a long variable that will store the converted number.
 * @param str A pointer to a character array (string) that contains the input
 * number as a string.
 * @param i The parameter "i" is used as a flag to indicate the context in which
 * the function is being called.
 * 
 * @return either 0 or 1. 0 represents a bad a command line argument has been
 * passed as an input, and 1 represents the argument is OK.
 */
static int	ft_atol_strict(long *nbr, char *str, long i)
{
	long	j;

	j = 0;
	while (is_space(str[j]) == true)
		j++;
	if (is_sign(str[j]) == true)
	{
		if (str[j] == '-')
		{
			*nbr = 1;
			return (0);
		}
		j++;
	}
	while (str[j] >= '0' && str[j] <= '9')
	{
		*nbr = *nbr * 10 + (str[j] - '0');
		j++;
	}
	if (str[j] || ((*nbr == 0) && (i == 1 || i == 5)) || *nbr > INT_MAX)
		return (0);
	return (1);
}

/**
 * The function `fill_data` assigns a given number `nbr` to a specific field in
 * a `t_table` struct based on the value of `i`.
 * 
 * @param table A pointer to a structure of type t_table. This structure likely
 * contains various fields related to a dining table, such as the number of
 * philosophers, the time it takes for a philosopher to die, the time it takes
 * for a philosopher to eat, the time it takes for a philosopher to sleep, and
 * @param nbr The value that needs to be assigned to the corresponding field in
 * the `table` structure.
 * @param i The parameter "i" is an integer that represents the index of the
 * data being filled in the t_table structure.
 */
static void	fill_data(t_table *table, long nbr, long i)
{
	if (i == 1)
		table->n_philos = nbr;
	if (i == 2)
		table->time_die = nbr;
	if (i == 3)
		table->time_eat = nbr;
	if (i == 4)
		table->time_sleep = nbr;
	if (i == 5)
		table->n_times_eat = nbr;
}

/**
 * The function ´args_parsing´ parses command line arguments and fills a data
 * structure with the parsed values.
 * 
 * @param table A pointer to a structure of type t_table.
 * @param argv An array of strings representing command line arguments.
 * 
 * @return an integer value as a flag.
 */
int	args_parsing(t_table *table, char **argv)
{
	long	i;
	long	nbr;

	memset(table, 0, sizeof(t_table));
	table->n_times_eat = -1;
	i = 0;
	nbr = 0;
	while (argv[++i])
	{
		if (ft_atol_strict(&nbr, argv[i], i) == 0)
		{
			if (i == 1 && nbr == 0)
				return (help(PHILOS_ZERO_ERROR), 1);
			else if (i == 5 && nbr == 0)
				return (help(N_EAT_ZERO_ERROR), 1);
			else if (nbr > INT_MAX)
				return (help(INT_MAX_ERROR), 1);
			else
				return (help(NUMBER_ERROR), 1);
		}
		else
			fill_data(table, nbr, i);
		nbr = 0;
	}
	return (0);
}
