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

#ifndef STRUCT_H
# define STRUCT_H
# include "../includes/codexion.h"

enum e_scheduler
{
	FIFO,
	EDF
};

enum e_dongle_status
{
	FREE,
	LOCK,
	COOLDOWN
};

typedef struct s_dongle
{
	pthread_mutex_t			mutex;;
	pthread_cond_t			cond;
	int						last_release;
	enum e_dongle_status	status;
} t_dongle;

typedef struct s_coders
{
	int				id;
	t_dongle		*left;
	t_dongle		*right;
	int				compiles_done;
	int				last_compile;
	int				left_index;
	int				right_index;
	struct s_data	*data;
	pthread_mutex_t	mutex;
}	t_coders;

typedef struct s_data
{
	long int			start;
	int					nb_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					nb_of_compiles;
	int					dongle_cooldown;
	enum e_scheduler	scheduler;
	t_coders			*coders;
	t_dongle			*dongle;
	bool				running;
	pthread_mutex_t		log_mutex;
}	t_data;

#endif