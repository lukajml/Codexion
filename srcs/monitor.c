/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:41:04 by lulauren          #+#    #+#             */
/*   Updated: 2026/10/07 15:41:11 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void	print_message(char *str, t_coder *coder, int id)
{
	size_t	time;

	pthread_mutex_lock(coder->burned_out)
}