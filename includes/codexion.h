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

//error.c
void	error_print(const char *msg);

//free.c
void	free_dongle(t_data *data);
void	free_mutex(t_data *data);
void	free_all(t_data *data);

//threads.c
void	start_simulation(t_data *data);

//routine.c
bool	should_stop(t_data *data);
void	set_stop(t_data *data);
void	*coder_routine(void *arg);

//time.c
long	get_time_ms(void);
long	time_since(long t);

//monitor.c
void	log_event(t_data *data, long ts, int id, const char *msg);
void	*monitor_routine(void *arg);

//dongle.c
void	take_dongle(t_coders *coder, t_dongle *dongle);
void	drop_dongle(t_dongle *dongle);
void	take_both(t_coders *coder);
void	drop_both(t_coders *coder);

#endif
