/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:25:18 by mguardia          #+#    #+#             */
/*   Updated: 2024/01/13 20:21:32 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/colors.h"

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
	if (args_parsing(&data, argv))
		return (EXIT_FAILURE);
	if (init_data(&data))
		return (EXIT_FAILURE);
	print_info(data);
	
	
	// printf("100ms - philo[1] has taken the fork.\n");
	// printf("100ms - philo[1] is eating.\n");
	// printf("100ms - philo[1] is thinking.\n");
	// printf("100ms - philo[1] is sleeping.\n");
	return (EXIT_SUCCESS);
}

/*
TODO:
	- parsear los argumentos OK
	- gestion de errores de argumentos OK
	- iniciar mutex fork OK
	- iniciar threads philos PENDING
	- asignar tenedores a los filosofos
	- mirar como se gestiona el tiempo gettimeofday()
	- gestionar acciones: coger tenedor, comer, dormir, pensar, morir
		timestamp_in_ms - philo[X] has taken a fork.
 		timestamp_in_ms - philo[X] is eating.
 		timestamp_in_ms - philo[X] is sleeping.
 		timestamp_in_ms - philo[X] is thinking.
 		timestamp_in_ms - philo[X] died.
	- liberar memoria, cerrar hilos y destruir mutex al acabar el programa
	- Revisar casos limite como que solo haya un philosofo, falte arg opcional,
	  no mas de 10ms entre mensaje y muerte de un philo (subject)...
	- revisar leaks
	- norminette
*/ 