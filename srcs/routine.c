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

static void	post_compile(t_coders *coder)
{
	drop_both(coder);
	if (should_stop(coder->data))
		return ;
	log_event(coder->data, get_time_ms(), coder->id, "is debugging");
	usleep(coder->data->time_to_debug * 1000);
	if (should_stop(coder->data))
		return ;
	log_event(coder->data, get_time_ms(), coder->id, "is refactoring");
	usleep(coder->data->time_to_refactor * 1000);
}

void	*coder_routine(void *arg)
{
	t_coders	*coder;
	long		timestamp;

	coder = (t_coders *)arg;
	pthread_mutex_lock(&coder->mutex);
	coder->last_compile = coder->data->start;
	pthread_mutex_unlock(&coder->mutex);
	while (!should_stop(coder->data)
		&& get_compiles(coder) < coder->data->nb_of_compiles)
	{
		if (!take_both(coder))
			return (NULL);
		timestamp = get_time_ms();
		pthread_mutex_lock(&coder->mutex);
		coder->last_compile = timestamp;
		coder->compiles_done++;
		pthread_mutex_unlock(&coder->mutex);
		log_event(coder->data, timestamp, coder->id, "is compiling");
		usleep(coder->data->time_to_compile * 1000);
		post_compile(coder);
	}
	return (NULL);
}
