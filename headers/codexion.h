/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 13:56:14 by lulauren          #+#    #+#             */
/*   Updated: 2026/10/05 15:19:58 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_heap_node
{
	long long	priority;
	int			coder_id;
}				t_heap_node;

typedef struct s_heap
{
	t_heap_node	*data;
	int			capacity;
	int			size;
}				t_heap;

typedef struct s_dongle
{
	pthread_mutex_t mutex;
	pthread_cond_t	cond;
	long long		last_released_time;
	t_heap			queue;
}				t_dongle;

typedef struct s_coder
{
	pthread_t		thread_id;
	int				id;
	int				nb_of_compiles;
	long long		last_compile_start;
	t_dongle		*right_dongle;
	t_dongle		*left_dongle;
	struct s_data	*global_data;
}				t_coder;

typedef struct s_data
{
	int				nb_of_coders;
	long long		time_to_burnout;
	long long		time_to_compile;
	long long		time_to_debug;
	long long		time_to_refactor;
	int				nb_of_compiles_required;
	long long		dongle_cooldown;
	int				scheduler_type;
	int				simulation_running;
	long long		start;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	log_mutex;
	t_dongle		*dongles;
	pthread_t		monitor_id;
}				t_data;

//parsing.c
int	parser(int ac, char **av);
int	check_all_nums(int ac, char **av);
int	is_valid_numeric(char *str);

//utils.c
int	ft_atoi(const char *nptr);
int	ft_strcmp(const char *s1, const char *s2);

#endif