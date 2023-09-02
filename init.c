/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiwon <chiwon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 21:54:01 by chiwon            #+#    #+#             */
/*   Updated: 2023/09/02 22:29:41 by chiwon           ###   ########.fr       */
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

int allocate_datas(t_philo *philo)
{
    philo->mutex.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
    if (!philo->mutex.forks)
    {
        printf("malloc error\n");
        return (0);
    }
    philo->tid = (pthread_t *)malloc(sizeof(pthread_t) * philo->num_of_philo);
    if (!philo->tid)
    {
        printf("malloc error\n");
        return (0);
    }
    philo->
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
    pthread_mutex_init(&data->mutex.write, NULL);
    pthread_mutex_init(&data->mutex.lock, NULL);
    return (1);
}