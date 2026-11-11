/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 10:18:11 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/11 12:02:36 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

int	main(int ac, char **av)
{
	t_data	data;
	
	if (!parser(ac, av))
		return (1);
	init_data(data);
}
