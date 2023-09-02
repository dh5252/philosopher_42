/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiwon <chiwon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:44:25 by chiwon            #+#    #+#             */
/*   Updated: 2023/09/02 15:54:47 by chiwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

# define PHILO_NUM 0
# define LIFE 1
# define EAT 2
# define SLEEP 3
# define LIMIT_EAT 4

typedef struct s_philo
{
    int argv[5];
}   t_philo;

int argument_parsing(int argc, char **argv, t_philo *philo);

#endif