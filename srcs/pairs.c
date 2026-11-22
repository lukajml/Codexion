/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 14:47:59 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/22 14:48:12 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

bool	take_both(t_coders *coder)
{
	if (coder->left == coder->right)
		return (take_dongle(coder, coder->left));
	if (coder->id % 2)
	{
		if (!take_dongle(coder, coder->right))
			return (false);
		if (!take_dongle(coder, coder->left))
		{
			drop_dongle(coder->right);
			return (false);
		}
		return (true);
	}
	if (!take_dongle(coder, coder->left))
		return (false);
	if (!take_dongle(coder, coder->right))
	{
		drop_dongle(coder->left);
		return (false);
	}
	return (true);
}

void	drop_both(t_coders *coder)
{
	drop_dongle(coder->left);
	if (coder->right != coder->left)
		drop_dongle(coder->right);
}
