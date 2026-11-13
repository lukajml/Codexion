/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 13:48:52 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/12 10:19:06 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	init_coders(t_data *data)
{
	int	i;

	data->coders = malloc(sizeof(t_coders) * data->nb_coders);
	if (!data->coders)
		error_print("Coders malloc failed.");
	i = 0;
	while (i < data->nb_coders)
	{
		data->coders[i] = (t_coders){
			.id = i + 1,
			.compiles_done = 0,
			.last_compile = 0,
			.left = &data->dongle[i],
			.right = &data->dongle[(i + 1) % data->nb_coders],
			.data = data
		};
		pthread_mutex_init(&data->coders[i].mutex, NULL);
		i++;
	}
}

void	init_dongle(t_data *data)
{
	int	i;

	data->dongle = malloc(sizeof(t_dongle) * data->nb_coders);
	if (!data->dongle)
		error_print("Dongle malloc failed.");
	i = 0;
	while (i < data->nb_coders)
	{
		pthread_mutex_init(&data->dongle[i].mutex, NULL);
		pthread_cond_init(&data->dongle[i].cond, NULL);
		data->dongle[i].last_release = 0;
		data->dongle[i].status = FREE;
		i++;
	}
}

void	init_data(t_data *data)
{
	init_dongle(data);
	init_coders(data);
	data->threads = malloc(sizeof(pthread_t) *data->nb_coders);
	if (!data->threads)
		error_print("Threads malloc failed.");
	pthread_mutex_init(&data->log_mutex, NULL);
	data->running = false;
}
