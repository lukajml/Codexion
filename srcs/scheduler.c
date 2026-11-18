/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:34:02 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/17 14:34:02 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

long	key_arrival(const t_wait_list *waiter)
{
	return (waiter->arrival);
}

long	key_daedline(const t_wait_list *waiter)
{
	return (waiter->deadline);
}

static void	heap_push(t_dongle *dongle, t_wait_list waiter, long (*key)(const t_wait_list *))
{
	
}
