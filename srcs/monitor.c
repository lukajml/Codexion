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

#include "../includes/codexion.h"

void	log_event(t_data *data, long ts, int id, const char *msg)
{
	pthread_mutex_lock(&data->log_mutex);
	printf("%ld %d %s\n", ts - data->start, id, msg);
	fflush(stdout);
	pthread_mutex_unlock(&data->log_mutex);
}
