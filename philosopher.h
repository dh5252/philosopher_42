/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:44:25 by chiwon            #+#    #+#             */
/*   Updated: 2023/09/16 15:50:26 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>

typedef struct s_philo
{
    pthread_mutex_t *lfork;
    pthread_mutex_t *rfork;
    struct timeval  last_eat;
    long long       eat_cnt;
    long long       id;
}   t_philo;

typedef struct s_base
{
    long long       num_of_philo;
    long long       time_to_die;
    long long       time_to_eat;
    long long       time_to_sleep;
    long long       min_eat_cnt;
    struct timeval  start;
    pthread_mutex_t *forks;
    pthread_t       *tid;
    t_philo         *philo;
}   t_base;

int argument_parsing(int argc, char **argv, t_base *philo);
int	ft_atol(const char *str);


#endif