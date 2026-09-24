/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulauren <luka.laurent@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 14:29:00 by lulauren          #+#    #+#             */
/*   Updated: 2026/09/24 14:29:11 by lulauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void*   foo(void* arg)
{
    printf("Thread is running\n");
}

int main()
{
    pthread_t   thread;

    pthread_create(&thread, NULL, foo, NULL);
    pthread_join(thread, NULL);
}

