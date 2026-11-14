/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:31:43 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/12 13:31:43 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

static void	join_coders(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coders)
		pthread_join(data->threads[i++], NULL);
}

static void	spawn_coders(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coders)
	{
		if (pthread_create(&data->threads[i],
				NULL, coder_routine, &data->coders[i]) != 0)
		{
			data->running = true;
			while (--i >= 0)
				pthread_join(data->threads[i], NULL);
			error_print("pthread_create failed.");
		}
		i++;
	}
}

static void	spawn_monitor(t_data *data)
{
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data) != 0)
	{
		data->running = true;
		join_coders(data);
		error_print("monitor pthread_create failed.");
	}
}

void	start_simulation(t_data *data)
{
	spawn_coders(data);
	spawn_monitor(data);
	data->start = get_time_ms();
	data->running = true;
	join_coders(data);
	pthread_join(data->monitor_thread, NULL);
}
