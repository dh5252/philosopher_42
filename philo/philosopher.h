/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:44:25 by chiwon            #+#    #+#             */
/*   Updated: 2023/09/24 00:55:54 by cahn             ###   ########.fr       */
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
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	last_eat_flag;
	struct timeval	last_eat;
	long long		eat_cnt;
	long long		id;
	struct s_base	*base;
}	t_philo;

typedef struct s_base
{
	long long		num_of_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		min_eat_cnt;
	long long		complete_eat_cnt;
	int				finish2;
	int				finish;
	pthread_mutex_t	complete_flag;
	pthread_mutex_t	finish2_flag;
	pthread_mutex_t	finish_flag;
	struct timeval	start;
	pthread_mutex_t	*forks;
	pthread_t		*tid;
	t_philo			*philo;
}	t_base;

int			argument_parsing(int argc, char **argv, t_base *philo);
int			ft_atol(const char *str);
int			print_state_with_finish(long long time, long long id, \
			char *message, t_base *base);
long long	get_millisec(struct timeval start);
void		start_routine(t_base *base);
void		mysleep(long long millisec);
void		destroy_mutex(t_base *base);
void		*scheduling(void *argv);
void		monitoring(t_base *base);
int			fork_controll(t_base *base, t_philo *philo);
int			sleeping(t_base *base, t_philo *philo);
int			eating(t_base *base, t_philo *philo);

#endif