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
#include <pthread.h>
#include <unistd.h>

static bool	should_stop(t_data *data)
{
	bool	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

void	*coder_routine(void *arg)
{
	t_coders	*coder = (t_coders *)arg;

	while (!coder->data->running)
		usleep(100);
	while (!should_stop(coder->data)
		&& coder->compiles_done < coder->data->nb_of_compiles)
	{
		take_both(coder);
		log_event(coder->data, get_time_ms(), coder->id, "compile");
		usleep(coder->data->time_to_compile * 1000);
		coder->compiles_done++;
		coder->last_compile = get_time_ms();
		drop_both(coder);
		log_event(coder->data, coder->last_compile, coder->id, "released");
		usleep(coder->data->time_to_debug * 1000);
		usleep(coder->data->time_to_refactor * 1000);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data = (t_data *)arg;

	while (!data->running)
		usleep(100);
	return (NULL);
}
