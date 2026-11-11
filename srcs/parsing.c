/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 13:54:26 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/11 10:46:43 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

int	is_valid_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_all_nums(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac - 1)
	{
		if (!is_valid_numeric(av[i]))
		{
			write(2, "ERROR: Arguments must be positive integers.\n", 44);
			return (0);
		}
		i++;
	}
	return (1);
}
// 
// int	parser(int ac, char **av, t_data *data)
// {
// 	if (ac != 9)
// 	{
// 		write(2, "ERROR: Invalid amount of arguments.\n", 36);
// 		return (0);
// 	}
// 	if (!check_all_nums(ac, av))
// 		return (0);
// 	if (atoi(av[1]) < 1)
// 	{
// 		write(2, "ERROR: There must be at least 1 coder.\n", 39);
// 		return (0);
// 	}
// 	if (strcmp(av[ac - 1], "fifo") != 0 && strcmp(av[ac -1], "edf") != 0)
// 	{
// 		write(2, "ERROR: Scheduler should be 'fifo' or 'edf'.\n", 44);
// 		return (0);
// 	}
// 	return (1);
// }


void	parsing(int ac, char **av, t_data *data)
{
	int	i;

	if (ac != 9)
		write(2, "Error: Invalid amount of args\n", 30);
	i = 0;
	while (i < 8)
		if (!check_all_nums(ac, av))
			error(); //All first 7 arguments must be positive integers.
	*data = (t_data){
		.nb_coders = atoi(av[1]),
		.time_to_burnout = atoi(av[2]),
		.time_to_compile = atoi(av[3]),
		.time_to_debug = atoi(av[4]),
		.time_to_refactor = atoi(av[5]),
		.nb_of_compiles = atoi(av[6]),
		.dongle_cooldown = atoi(av[7]),
		.scheduler = strcmp(av[8], "fifo" || "edf") //?????
	};
	if (!data->nb_coders ||
		!data->time_to_burnout ||
		!data->time_to_compile ||
		!data->time_to_debug ||
		!data->time_to_refactor)
		error(); //number_of_coders, time_to_burnout, time_to_compile,time_to_debug and time_to_refactor must be greater than 0.
}