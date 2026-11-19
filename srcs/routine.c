/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 12:17:17 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/14 15:09:53 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

bool	should_stop(t_data *data)
{
	bool	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = true;
	pthread_mutex_unlock(&data->stop_mutex);
}

static int	get_compiles(t_coders *coder)
{
	int	done;

	pthread_mutex_lock(&coder->mutex);
	done = coder->compiles_done;
	pthread_mutex_unlock(&coder->mutex);
	return (done);
}

void	*coder_routine(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	pthread_mutex_lock(&coder->mutex);
	coder->last_compile = coder->data->start;
	pthread_mutex_unlock(&coder->mutex);
	while (!should_stop(coder->data)
		&& get_compiles(coder) < coder->data->nb_of_compiles)
	{
		take_both(coder);
		log_event(coder->data, get_time_ms(), coder->id, "is compiling");
		usleep(coder->data->time_to_compile * 1000);
		pthread_mutex_lock(&coder->mutex);
		coder->compiles_done++;
		coder->last_compile = get_time_ms();
		pthread_mutex_unlock(&coder->mutex);
		drop_both(coder);
		usleep(coder->data->time_to_debug * 1000);
		log_event(coder->data, get_time_ms(), coder->id, "is debugging");
		usleep(coder->data->time_to_refactor * 1000);
		log_event(coder->data, get_time_ms(), coder->id, "is refactoring");
	}
	return (NULL);
}
