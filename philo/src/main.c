/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:25:18 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/28 13:39:16 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/colors.h"
#include "../inc/error.h"

// void	leaks(void)
// {
// 	system("leaks -q philo");
// }

int	main(int argc, char **argv)
{
	t_table	table;

	// atexit(leaks);
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

/*
TODO:
	- parsear los argumentos OK
	- gestion de errores de argumentos OK
	- iniciar mutex fork OK
	- iniciar threads philos OK
	- asignar tenedores a los filosofos OK
	- mirar como se gestiona el tiempo gettimeofday() OK
	- gestionar acciones: coger tenedor, comer, dormir, pensar, morir
		timestamp_in_ms - philo[X] has taken a fork. OK
 		timestamp_in_ms - philo[X] is eating. OK
 		timestamp_in_ms - philo[X] is sleeping. OK
 		timestamp_in_ms - philo[X] is thinking. OK
 		timestamp_in_ms - philo[X] died. OK
	- Revisar casos limite como que solo haya un philosofo, falte arg opcional,
	  no mas de 10ms entre mensaje y muerte de un philo (subject)... OK
	- norminette OK
	- liberar memoria, cerrar hilos y destruir mutex al acabar el programa OK
	- revisar leaks en fallos previos a la simulacion PENDING
*/ 