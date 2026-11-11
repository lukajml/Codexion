/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 10:22:09 by lulauren          #+#    #+#             */
/*   Updated: 2026/11/11 11:25:53 by lulauren         ###   ########.fr       */
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
int	parser(int ac, char **av, t_data *data);
int	check_all_nums(int ac, char **av);
int	is_valid_numeric(char *str);

//utils.c
int	error(void);

#endif
