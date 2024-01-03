/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:25:18 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/03 17:27:42 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	leaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_all	data;

	atexit(leaks);
	if (argc != 5 && argc != 6)
		return (help(ARGC_ERROR), EXIT_FAILURE);
	if (init_data(&data, argv) == false)
		return (EXIT_FAILURE);
	printf("TODO OK HASTA AQUI\n");
	return (EXIT_SUCCESS);
}
