/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:41:04 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/18 11:17:37 by lulauren         ###   ########.fr       */
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

static int	sweep(t_data *data, long now)
{
	int			i;
	int			done;
	t_coders	*coder;
	int			done_compiles;
	long		timestamp;

	done = 0;
	i = 0;
	while (i < data->nb_coders)
	{
		coder = &data->coders[i++];
		pthread_mutex_lock(&coder->mutex);
		done_compiles = coder->compiles_done;
		timestamp = coder->last_compile;
		pthread_mutex_unlock(&coder->mutex);
		if (done_compiles >= data->nb_of_compiles)
			done++;
		else if (now - timestamp >= data->time_to_burnout)
		{
			log_event(data, now, coder->id, "burned out");
			set_stop(data);
			return (-1);
		}
	}
	return (done);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	long	now;
	int		done;

	data = (t_data *)arg;
	while (!should_stop(data))
	{
		usleep(1000);
		now = get_time_ms();
		done = sweep(data, now);
		if (done == data->nb_coders)
			set_stop(data);
	}
	return (NULL);
}
