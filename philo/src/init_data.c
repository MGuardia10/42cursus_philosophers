/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:54:06 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/03 17:26:48 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atosize_t(size_t *nbr, char *str, size_t i)
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

t_bool	is_valid_arg(size_t *nbr, char *str, size_t i)
{
	int	flag;

	flag = ft_atosize_t(nbr, str, i);
	if (flag == 0)
		return (false);
	return (true);
}

void	fill_data(t_all *data, size_t nbr, size_t i)
{
	if (i == 1)
	{
		data->n_philos = nbr;
		data->n_forks = nbr;
	}
	if (i == 2)
		data->time_die = nbr;
	if (i == 3)
		data->time_eat = nbr;
	if (i == 4)
		data->time_sleep = nbr;
	if (i == 5)
		data->n_times_eat = nbr;
}

t_bool	init_data(t_all *data, char **argv)
{
	size_t	i;
	size_t	nbr;

	i = 1;
	memset(data, 0, sizeof(t_all));
	nbr = 0;
	while (argv[i])
	{
		if (is_valid_arg(&nbr, argv[i], i) == false)
		{
			if (i == 1 && nbr == 0)
				return (help(N_PHILOS_ZERO), false);
			else if (i == 5 && nbr == 0)
				return (help(N_TIMES_EAT_ZERO), false);
			else
				return (help(NUMBER_ERROR), false);
		}
		else
			fill_data(data, nbr, i);
		nbr = 0;
		i++;
	}
	// printf("n_philos --> %zu\n", data->n_philos);
	// printf("n_forks --> %zu\n", data->n_forks);
	// printf("time_die --> %zu\n", data->time_die);
	// printf("time_eat --> %zu\n", data->time_eat);
	// printf("time_sleep --> %zu\n", data->time_sleep);
	// printf("n_times_eat --> %zu\n", data->n_times_eat);
	return (true);
}
