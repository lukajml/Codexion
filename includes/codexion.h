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

//parsing.c
int	parser(int ac, char **av);
int	check_all_nums(int ac, char **av);
int	is_valid_numeric(char *str);

//utils.c
int	ft_atoi(const char *nptr);
int	ft_strcmp(const char *s1, const char *s2);

#endif
