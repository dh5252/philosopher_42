/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 21:54:01 by chiwon            #+#    #+#             */
/*   Updated: 2023/09/16 15:55:06 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int arguments_valid(int argc, char **argv)
{
    int i;
    int j;

    if (!(argc == 5 || argc == 6))
    {
        printf("argument number error\n");
        return (0);
    }
    i = 1;
    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
            {
                printf("argument value error\n");
                return (0);
            }
            ++j;
        }
        ++i;
    }
    return (1);
}

int allocate_datas(t_base *base)
{
    base->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * base->num_of_philo);
    if (!base->forks)
    {
        printf("malloc error\n");
        return (0);
    }
    base->tid = (pthread_t *)malloc(sizeof(pthread_t) * base->num_of_philo);
    if (!base->tid)
    {
        printf("malloc error\n");
        return (0);
    }
    base->philo = (t_philo *)malloc(sizeof(t_philo) * base->num_of_philo);
    if (!base->philo)
    {
        printf("malloc error\n");
        return (0);
    }
    memset(base->philo, 0, sizeof(base->philo));
    return (1);
}

void    init_value(t_base *base)
{
    int i;

    i = 0;
    while (++i < base->num_of_philo)
    {
        base->philo[i].rfork = &base->forks[i - 1];
        base->philo[i].lfork = &base->forks[i];
    }
    base->philo[0].rfork = &base->forks[base->num_of_philo - 1];
    base->philo[0].lfork = &base->forks[0];
    i = 0;
    while (i < base->num_of_philo)
    {
        base->philo[i].eat_cnt = 0;
        base->philo[i].id = i;
        base->philo[i++].eat_cnt = base->min_eat_cnt;
    }
}

int argument_parsing(int argc, char **argv, t_base *data)
{
    if (!arguments_valid(argc, argv))
        return (0);
    data->num_of_philo = ft_atol(argv[1]);
    data->time_to_die = ft_atol(argv[2]);
    data->time_to_eat = ft_atol(argv[3]);
    data->time_to_sleep = ft_atol(argv[4]);
    if (argc == 5)
        data->min_eat_cnt = -1;
    else
        data->min_eat_cnt = ft_atol(argv[5]);
    if (!allocate_datas(data->philo))
        return (0);
    init_value(data);
    return (1);
}