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
	{
		i++;
		if (str[i] == '\0')
			return (0);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_all_nums(char **av)
{
	int	i;

	i = 1;
	while (i <= 7)
	{
		if (!is_valid_numeric(av[i]))
			return (0);
		i++;
	}
	return (1);
}

void	parser(int ac, char **av, t_data *data)
{
	if (ac != 9)
		error_print("Invalid amount of arguments: expected 8 arguments.");
	if (!check_all_nums(av))
		error_print("The 7 first arguments must be positive integers.");
	if (strcmp(av[8], "fifo") != 0 && strcmp(av[8], "edf") != 0)
		error_print("Last argument must be \"fifo\" or \"edf\".");
	*data = (t_data){
		.nb_coders = atoi(av[1]),
		.time_to_burnout = atoi(av[2]),
		.time_to_compile = atoi(av[3]),
		.time_to_debug = atoi(av[4]),
		.time_to_refactor = atoi(av[5]),
		.nb_of_compiles = atoi(av[6]),
		.dongle_cooldown = atoi(av[7]),
		.scheduler = strcmp(av[8], "edf") == 0
	};
	if (!data->nb_coders
		|| !data->time_to_burnout
		|| !data->time_to_compile
		|| !data->time_to_debug
		|| !data->time_to_refactor)
		error_print("The arguments must be greater than 0.");
}
