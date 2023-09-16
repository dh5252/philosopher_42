/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:06:56 by cahn              #+#    #+#             */
/*   Updated: 2023/09/16 22:56:17 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    monitoring(t_base *base)
{
    int i;

    while (1)
    {
        i = 0;
        pthread_mutex_lock(&base->complete_flag);
        if (base->complete_eat_cnt == base->num_of_philo)
        {
            pthread_mutex_unlock(&base->complete_flag);
            return ;
        }
        pthread_mutex_unlock(&base->complete_flag);
        while (i < base->num_of_philo)
        {
            if (get_millisec(base->philo[i].last_eat) >= base->time_to_die)
            {
                print_state(get_millisec(base->philo[i].start_thread), base->philo[i].id + 1, "died", base);
                pthread_mutex_lock(&base->dead_flag);
                if (base->dead)
                {
                    pthread_mutex_unlock(&base->dead_flag);
                    return ;
                }
                pthread_mutex_unlock(&base->dead_flag);
                base->dead = 1;
                return ;
            }
            ++i;
        }
        usleep(200);
    }
}

int sleeping(t_base *base, t_philo *philo)
{
    if (!print_state(get_millisec(philo->start_thread), philo->id + 1, "is sleeping", base))
        return (0);
    mysleep(base->time_to_sleep);
    return (1);
}

void routine(t_base *base, t_philo *philo)
{
    int             lf;
    int             rf;

    rf = pthread_mutex_lock(philo->rfork);
    if (!rf && !print_state(get_millisec(philo->start_thread), philo->id + 1, "has taken a fork", base))
        return ; 
    lf = pthread_mutex_lock(philo->lfork);
    if (!lf && !print_state(get_millisec(philo->start_thread), philo->id + 1, "has taken a fork", base))
        return ;
    if (!lf && !rf)
    {
        if (!print_state(get_millisec(philo->start_thread), philo->id + 1, "is eating", base))
            return ;
        mysleep(base->time_to_eat);
        gettimeofday(&philo->last_eat, NULL);
        if (base->num_of_philo & 1)
        {
            if (philo->id == base->num_of_philo - 1)
                base->exclude_id += 2;
            else if (philo->id == base->num_of_philo - 3 && base->exclude_id == base->num_of_philo - 1)
                base->exclude_id = (base->exclude_id + 2) % base->num_of_philo;
        }
        philo->eat_cnt--;
        pthread_mutex_unlock(philo->rfork);
        pthread_mutex_unlock(philo->lfork);
        sleeping(base, philo);
        if (!print_state(get_millisec(philo->start_thread), philo->id + 1, "is thinking", base))
            return ;
    }
    else
        printf("error\n");
}

void    *scheduling(void *argv)
{
    t_philo *philo;
    t_base  *base;

    philo = (t_philo *)argv;
    base = philo->base;
    if (philo->id & 1)
        usleep(100);
    while (1)
    {
        pthread_mutex_lock(&base->complete_flag);
        if (base->complete_eat_cnt == base->num_of_philo)
        {
            pthread_mutex_unlock(&base->complete_flag);
            break ;
        }
        pthread_mutex_unlock(&base->complete_flag);
        pthread_mutex_lock(&base->dead_flag);
        if (base->dead)
        {
            pthread_mutex_unlock(&base->dead_flag);
            break ;
        }
        pthread_mutex_unlock(&base->dead_flag);
        if (philo->id != base->exclude_id) 
            routine(base, philo);
        else
            mysleep(base->time_to_eat + base->time_to_sleep);
        pthread_mutex_lock(&base->complete_flag);
        if (philo->eat_cnt == 0)
            base->complete_eat_cnt++;
        pthread_mutex_unlock(&base->complete_flag);
    }
    return (0);
}

void    start_routine(t_base *base)
{
    int i;

    i = 0;
    base->exclude_id = -1;
    if (base->num_of_philo & 1)
        base->exclude_id = 0;
    pthread_mutex_init(&base->dead_flag, NULL);
    pthread_mutex_init(&base->complete_flag, NULL);
    base->dead = 0;
    while (i < base->num_of_philo)
    {
        gettimeofday(&base->philo[i].start_thread, NULL);
        base->philo[i].last_eat = base->philo[i].start_thread;
        if (pthread_create(&base->tid[i], NULL, scheduling, &base->philo[i]))
            return ;
        ++i;
    }
    monitoring(base);
    i = 0;
    while (i < base->num_of_philo)
        pthread_join(base->tid[i++], NULL);
    destroy_mutex(base);
}