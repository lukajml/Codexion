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
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <unistd.h>

static bool	takeable(t_dongle *dongle, t_data *data)
{
	return (dongle->status == FREE 
		&& get_time_ms() - dongle->last_release >= data->dongle_cooldown);
}

void	take_dongle(t_coders *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	while (!takeable(dongle, coder->data))
	{
		if (dongle->status == FREE)
		{
			pthread_mutex_unlock(&dongle->mutex);
			usleep((data->dongle_cooldown 
				- (get_time_ms() - dongle->last_release)) * 1000);
			pthread_mutex_lock(&dongle->mutex);
		}
		else
			pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
	dongle->status = LOCK;
	pthread_mutex_unlock(&dongle->mutex);
}

void	drop_dongle(t_coders *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->status = FREE;
	dongle->last_release = get_time_ms();
	pthread_mutex_unlock(&dongle->mutex);
	pthread_cond_broadcast(&dongle->cond);
}

void	take_both(t_coders *coder)
{
	if (coder->left == coder->right)
		take_dongle(coder, coder->left);
	else if (coder->id % 2)
	{
		take_dongle(coder, coder->right);
		take_dongle(coder, coder->left);
	}
	else
	{
		take_dongle(coder, coder->left);
		take_dongle(coder, coder->right);
	}
}

void	drop_both(t_coders *coder)
{
	drop_dongle(coder, coder->left);
	if (coder->right != coder->left)
		drop_dongle(coder, coder->right);
}