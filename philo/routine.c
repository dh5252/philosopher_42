/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiwon <chiwon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:06:56 by cahn              #+#    #+#             */
/*   Updated: 2023/09/17 18:38:52 by chiwon           ###   ########.fr       */
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
                base->dead = 1;
                pthread_mutex_unlock(&base->dead_flag);
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

int take_rfork(t_philo *philo, t_base *base)
{
    int rf;

    rf = pthread_mutex_lock(philo->rfork);
    if (!rf && !print_state(get_millisec(philo->start_thread), philo->id + 1, "has taken a fork", base))
    {
        pthread_mutex_unlock(philo->rfork);
        return (0); 
    }
    return (1);
}

int take_lfork(t_philo *philo, t_base *base)
{
    int lf;

    lf = pthread_mutex_lock(philo->lfork);
    if (!lf && !print_state(get_millisec(philo->start_thread), philo->id + 1, "has taken a fork", base))
    {
        pthread_mutex_unlock(philo->lfork);
        return (0); 
    }
    return (1);
}

void routine(t_base *base, t_philo *philo)
{
    if ((philo->id & 1))
    {
        if (!take_rfork(philo, base)) 
            return ;
        if (!take_lfork(philo, base))
        {
            pthread_mutex_unlock(philo->rfork);
            return ;
        }
    }
    else 
    {
        if (!take_lfork(philo, base)) 
            return ;
        if (!take_rfork(philo, base))
        {
            pthread_mutex_unlock(philo->lfork);
            return ;
        }
    }
    if (!print_state(get_millisec(philo->start_thread), philo->id + 1, "is eating", base))
        return ;
    mysleep(base->time_to_eat);
    gettimeofday(&philo->last_eat, NULL);
    if (base->num_of_philo & 1)
    {
        pthread_mutex_lock(&base->exclude_flag);
        if (philo->id == base->num_of_philo - 1)
            base->exclude_id += 2;
        else if (philo->id == base->num_of_philo - 3 && base->exclude_id == base->num_of_philo - 1)
            base->exclude_id = (base->exclude_id + 2) % base->num_of_philo;
        pthread_mutex_unlock(&base->exclude_flag);
    }
    philo->eat_cnt--;
    pthread_mutex_unlock(philo->rfork);
    pthread_mutex_unlock(philo->lfork);
    sleeping(base, philo);
    if (!print_state(get_millisec(philo->start_thread), philo->id + 1, "is thinking", base))
        return ;
    
    
}

void    *scheduling(void *argv)
{
    t_philo *philo;
    t_base  *base;

    philo = (t_philo *)argv;
    base = philo->base;
    philo->start_thread = base->start;
    philo->last_eat = base->start;
    if (philo->id & 1)
        usleep(10);
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
        pthread_mutex_lock(&base->exclude_flag);
        if (philo->id != base->exclude_id)
        {
            pthread_mutex_unlock(&base->exclude_flag);
            routine(base, philo);
        }
        else
        {
            pthread_mutex_unlock(&base->exclude_flag);
            mysleep(base->time_to_eat + base->time_to_sleep);
        }
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
    gettimeofday(&base->start, NULL);
    pthread_mutex_init(&base->exclude_flag, NULL);
    pthread_mutex_init(&base->dead_flag, NULL);
    pthread_mutex_init(&base->complete_flag, NULL);
    base->dead = 0;
    while (i < base->num_of_philo)
    {
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