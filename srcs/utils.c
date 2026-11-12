/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 13:56:17 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/11 13:56:17 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

int	error_print(char *msg)
{
	if (msg)
	{
		write(STDERR_FILENO, "Error: ", 7);
		write(STDERR_FILENO, msg, strlen(msg));
	}
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}
