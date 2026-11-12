/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:31:38 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/12 14:31:38 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	free_dongle(t_data *data)
{
	int	i;

	if (!data->dongle)
		return ;
	i = 0;
	while (i < data->nb_coders)
	{
		pthread_mutex_destroy(&data->dongle[i].mutex);
		pthread_cond_destroy(&data->dongle[i].cond);
		i++;
	}
	free(data->dongle);
	data->dongle = NULL;
}

void	free_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coders)
		pthread_mutex_destroy(&data->coders[i++].mutex);
	pthread_mutex_destroy(&data->log_mutex);
}

void	free_all(t_data *data)
{
	if (!data)
		return ;
	free_dongle(data);
	free_mutex(data);
	if (data->coders)
	{
		free(data->coders);
		data->coders = NULL;
	}
}
