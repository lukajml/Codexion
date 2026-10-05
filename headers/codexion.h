/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 13:56:14 by lulauren          #+#    #+#             */
/*   Updated: 2026/10/05 15:13:09 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#ifndef CODEXION_H
# define CODEXION_H

//parsing.c
int	parser(int ac, char **av);
int	check_all_nums(int ac, char **av);
int	is_valid_numeric(char *str);

//utils.c
int	ft_atoi(const char *nptr);
int	ft_strcmp(const char *s1, const char *s2);

#endif