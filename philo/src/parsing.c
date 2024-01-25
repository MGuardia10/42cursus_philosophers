/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:54:06 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/25 19:53:39 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/error.h"

static int	ft_atosize_t(size_t *nbr, char *str, size_t i)
{
	size_t	j;

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
	if (str[j] || ((*nbr == 0) && (i == 1 || i == 5)))
		return (0);
	return (1);
}

static bool	is_valid_arg(size_t *nbr, char *str, size_t i)
{
	int	flag;

	flag = ft_atosize_t(nbr, str, i);
	if (flag == 0)
		return (false);
	return (true);
}

static void	fill_data(t_all *data, size_t nbr, size_t i)
{
	if (i == 1)
		data->n_philos = nbr;
	if (i == 2)
		data->time_die = nbr;
	if (i == 3)
		data->time_eat = nbr;
	if (i == 4)
		data->time_sleep = nbr;
	if (i == 5)
		data->n_times_eat = nbr;
}

int	args_parsing(t_all *data, char **argv)
{
	size_t	i;
	size_t	nbr;

	i = 1;
	memset(data, 0, sizeof(t_all));
	data->n_times_eat = -1;
	nbr = 0;
	while (argv[i])
	{
		if (is_valid_arg(&nbr, argv[i], i) == 0)
		{
			if (i == 1 && nbr == 0)
				return (help(PHILOS_ZERO_ERROR), 1);
			else if (i == 5 && nbr == 0)
				return (help(N_EAT_ZERO_ERROR), 1);
			else
				return (help(NUMBER_ERROR), 1);
		}
		else
			fill_data(data, nbr, i);
		nbr = 0;
		i++;
	}
	return (0);
}
