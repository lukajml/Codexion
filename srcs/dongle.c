/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 13:41:09 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/14 13:41:09 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

static bool	wins_dongle(t_coders *coder, t_dongle *dongle)
{
	return (dongle->status == FREE
		&& get_time_ms() - dongle->last_release >= coder->data->dongle_cooldown
		&& dongle->size > 0
		&& dongle->waiters[0].coder == coder->id);
}

static void	queue_wait(t_coders *coder, t_dongle *dongle, long deadline,
	bool *queued)
{
	t_waiter	waiter;

	waiter.coder = coder->id;
	waiter.arrival = get_time_ms();
	if (coder->data->scheduler == EDF)
		waiter.key = deadline;
	else
		waiter.key = waiter.arrival;
	heap_push(dongle, &waiter);
	*queued = true;
}

bool	take_dongle(t_coders *coder, t_dongle *dongle)
{
	bool	queued;
	long	deadline;

	pthread_mutex_lock(&coder->mutex);
	deadline = coder->last_compile + coder->data->time_to_burnout;
	pthread_mutex_unlock(&coder->mutex);
	pthread_mutex_lock(&dongle->mutex);
	queued = false;
	while (!wins_dongle(coder, dongle))
	{
		if (should_stop(coder->data))
		{
			pthread_mutex_unlock(&dongle->mutex);
			return (false);
		}
		if (!queued)
			queue_wait(coder, dongle, deadline, &queued);
		pthread_mutex_unlock(&dongle->mutex);
		usleep(1000);
		pthread_mutex_lock(&dongle->mutex);
	}
	heap_pop(dongle);
	dongle->status = LOCK;
	pthread_mutex_unlock(&dongle->mutex);
	log_event(coder->data, get_time_ms(), coder->id, "has taken a dongle");
	return true;
}

void	drop_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->status = FREE;
	dongle->last_release = get_time_ms();
	pthread_mutex_unlock(&dongle->mutex);
}