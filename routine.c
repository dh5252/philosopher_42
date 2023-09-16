/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:06:56 by cahn              #+#    #+#             */
/*   Updated: 2023/09/16 15:57:47 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    monitoring(t_base *base)
{

}

void    *routine(void *argv)
{
    t_philo *philo;

    philo = (t_philo *)argv;
    if (philo->id & 1)
        usleep(10);
    while (1)
    {
        
    }
}

int start_routine(t_base *base)
{
    int i;

    i = 0;
    while (i < base->num_of_philo)
    {
        gettimeofday(&base->philo[i].last_eat, NULL);
        if (pthread_create(&base->tid[i], NULL, routine, &base->philo[i]))
            return (1);
        ++i;
    }

}