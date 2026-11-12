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
#include <string.h>

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

void	parser(int ac, char **av, t_data *data)
{
	int	i;

	if (ac != 9)
		write(2, "Error: Invalid amount of args\n", 30);
	i = 0;
	while (i < 8)
		if (!check_all_nums(ac, av))
			error_print("The 7 first arguments must be positive integers.");
	*data = (t_data){
		.nb_coders = atoi(av[1]),
		.time_to_burnout = atoi(av[2]),
		.time_to_compile = atoi(av[3]),
		.time_to_debug = atoi(av[4]),
		.time_to_refactor = atoi(av[5]),
		.nb_of_compiles = atoi(av[6]),
		.dongle_cooldown = atoi(av[7]),
		.scheduler = strcmp(av[8], "fifo") || strcmp(av[8], "edf")
	};
	if (!data->nb_coders
		|| !data->time_to_burnout
		|| !data->time_to_compile
		|| !data->time_to_debug
		|| !data->time_to_refactor)
		error_print("The arguments must be greater than 0.");
}
