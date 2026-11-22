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

static void	swp(t_waiter *a, t_waiter *b)
{
	t_waiter	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static bool	sorts_first(t_waiter *a, t_waiter *b)
{
	if (a->key != b->key)
		return (a->key < b->key);
	if (a->arrival != b->arrival)
		return (a->arrival < b->arrival);
	return (a->coder < b->coder);
}

static void	sift(t_dongle *dongle, int i)
{
	int	child;
	int	parent;

	child = 2 * i + 1;
	while (child < dongle->size)
	{
		if (child + 1 < dongle->size
			&& sorts_first(&dongle->waiters[child + 1],
				&dongle->waiters[child]))
			child++;
		if (!sorts_first(&dongle->waiters[child], &dongle->waiters[i]))
			break ;
		swp(&dongle->waiters[child], &dongle->waiters[i]);
		i = child;
		child = 2 * i + 1;
	}
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (!sorts_first(&dongle->waiters[i], &dongle->waiters[parent]))
			return ;
		swp(&dongle->waiters[i], &dongle->waiters[parent]);
		i = parent;
	}
}

void	heap_push(t_dongle *dongle, t_waiter *waiter)
{
	dongle->waiters[dongle->size] = *waiter;
	dongle->size++;
	sift(dongle, dongle->size - 1);
}

void	heap_pop(t_dongle *dongle)
{
	if (dongle->size == 0)
		return ;
	dongle->waiters[0] = dongle->waiters[dongle->size - 1];
	dongle->size--;
	sift(dongle, 0);
}
