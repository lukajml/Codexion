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

typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	int				compiling;
	int				compiles;
	int				nb_of_coders;
	int				*burned_out;
	size_t			time_to_burnout;
	size_t			time_to_compile;
	size_t			time_to_debug;
	size_t			time_to_refactor;
	phtread_mutex_t	*r_dongle;
	phtread_mutex_t	*l_dongle;
	phtread_mutex_t	*burnout_lock;
	phtread_mutex_t	*compile_lock;
}				t_coder;

typedef struct s_program
{
	int				burnout_flag;
	phtread_mutex_t	*burnout_lock;
	phtread_mutex_t	*compile_lock;
	t_coder			*coders;
}				t_program;

//parsing.c
int	parser(int ac, char **av);
int	check_all_nums(int ac, char **av);
int	is_valid_numeric(char *str);

//utils.c
int	ft_atoi(const char *nptr);
int	ft_strcmp(const char *s1, const char *s2);

#endif