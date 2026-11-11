/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 11:51:15 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/11 11:51:15 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef enum e_dongle_status
{
	FREE,
	LOCK,
	COOLDOWN
}	t_dongle_status;

typedef struct s_dongle
{
	t_dongle_status	status;
} t_dongle;

typedef struct s_coders
{
	int				id;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	int				compiles_done;
	int				last_compile;
	int				left_index;
	int				right_index;
	struct s_data	*data;
}	t_coders;

typedef struct s_data
{
	long int	start;
	int			nb_coder;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			nb_of_compiles;
	int			dongle_cooldown;
	t_scheduler	scheduler;
	t_coders	*coders;
	t_dongle	*dongle;
	bool		running;
}	t_data;