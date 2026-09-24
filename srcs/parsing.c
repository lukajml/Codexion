/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 13:54:26 by lulauren          #+#    #+#             */
/*   Updated: 2026/09/24 18:03:18 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

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

	i = 0;
	while (i < ac - 1)
	{
		if (!is_valid_numeric(av[1]))
		{
			write(2, "ERROR: Arguments must be positive integers.\n", 44);
			return (0);
		}
		i++;
	}
	return (1);
}

int	parser(int ac, char **av)
{
	if (ac != 8)
	{
		write(2, "ERROR: Invalid amount of arguments.\n", 36);
		return (0);
	}
	if (!check_all_nums(ac, av))
		return (0);
	return (1);
}