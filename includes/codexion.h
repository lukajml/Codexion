/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 10:22:09 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/12 10:17:34 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "../includes/struct.h"

//init.c
void	init_coders(t_data *data);
void	init_dongle(t_data *data);
void	init_data(t_data *data);

//parsing.c
void	parser(int ac, char **av, t_data *data);
int		check_all_nums(char **av);
int		is_valid_numeric(char *str);

//utils.c
int		error_print(char *msg);

//free.c
void	free_dongle(t_data *data);
void	free_mutex(t_data *data);
void	free_all(t_data *data);

//threads.c

//monitor.c

//routine.c

#endif
