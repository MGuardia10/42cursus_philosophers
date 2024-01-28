/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:25:18 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/28 16:43:17 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/colors.h"
#include "../inc/error.h"

void	leaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_table	table;

	atexit(leaks);
	if (argc != 5 && argc != 6)
		return (help(ARGC_ERROR), EXIT_FAILURE);
	if (args_parsing(&table, argv))
		return (EXIT_FAILURE);
	if (init_data(&table))
		return (EXIT_FAILURE);
	print_info(table);
	if (start_simulation(&table))
		return (EXIT_FAILURE);
	safe_exit(&table);
	return (EXIT_SUCCESS);
}
