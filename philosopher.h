/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiwon <chiwon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:44:25 by chiwon            #+#    #+#             */
/*   Updated: 2023/09/02 22:32:23 by chiwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_mutex
{
    pthread_mutex_t *forks;
    pthread_mutex_t lock;
    pthread_mutex_t write;
}   t_mutex;

typedef struct s_philo
{
    int tmp;
}   t_philo;

typedef struct s_base
{
    long long   num_of_philo;
    long long   time_to_die;
    long long   time_to_eat;
    long long   time_to_sleep;
    long long   min_eat_cnt;
    t_mutex     mutex;
    pthread_t   *tid;
}   t_base;

int argument_parsing(int argc, char **argv, t_base *philo);
int	ft_atol(const char *str);


#endif