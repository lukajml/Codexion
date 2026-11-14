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

void	*monitor_routine(void *arg)
{
	t_data		*data;
	t_coders	*coder;
	long		now;
	int			done;
	int			i;

	data = (t_data *)arg;
	while (!data->running)
		usleep(100);
	while (!should_stop(data))
	{
		usleep(1000);
		now = get_time_ms();
		done = 0;
		i = 0;
		while (i <data->nb_coders)
		{
			coder = &data->coders[i++];
			if (coder->compiles_done >= data->nb_of_compiles)
				done++;
			else if (now - coder->last_compile + data->time_to_compile
				>= data->time_to_burnout)
			{
				log_event(data, now, coder->id, "burned out");
				set_stop(data);
				return (NULL);
			}
		}
		if (done == data->nb_coders)
		{
			log_event(data, now, 0, "all done");
			set_stop(data);
			return (NULL);
		}
	}
	return (NULL);
}