/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 12:17:17 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/12 12:17:17 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	*coder_routine(void *arg)
{
	t_coders	*me = (t_coders *)arg;

	while (!me->data->running)
		usleep(100);
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data = (t_data *)arg;

	while (!data->running)
		usleep(100);
	return (NULL);
}
