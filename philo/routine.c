/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:06:56 by cahn              #+#    #+#             */
/*   Updated: 2023/09/18 02:38:33 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	start_routine(t_base *base)
{
	int	i;

	i = 0;
	pthread_mutex_init(&base->dead_flag, NULL);
	pthread_mutex_init(&base->complete_flag, NULL);
	pthread_mutex_init(&base->finish_flag, NULL);
	gettimeofday(&base->start, NULL);
	base->dead = 0;
	while (i < base->num_of_philo)
	{
		base->philo[i].last_eat = base->start;
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

int	sleeping(t_base *base, t_philo *philo)
{
	if (!print_state(get_millisec(base->start), philo->id + 1, \
			"is sleeping", base))
		return (0);
	mysleep(base->time_to_sleep);
	return (1);
}

void	routine(t_base *base, t_philo *philo)
{
	if (!fork_controll(base, philo))
		return ;
	if (!print_state(get_millisec(base->start), philo->id + 1, \
		"is eating", base))
		return ;
	pthread_mutex_lock(&philo->last_eat_flag);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(&philo->last_eat_flag);
	mysleep(base->time_to_eat);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
	philo->eat_cnt--;
	sleeping(base, philo);
	if (philo->id % 2 == 0)
		usleep(200);
	if (!print_state(get_millisec(base->start), philo->id + 1, \
		"is thinking", base))
		return ;
}

void	preprocessing(t_base **base, t_philo **philo, void *argv)
{
	*philo = (t_philo *)argv;
	*base = (*philo)->base;
	if ((*philo)->id & 1)
		usleep(20);
	if (((*base)->num_of_philo & 1) && (*philo)->id == 0)
		usleep(100);
}

void	*scheduling(void *argv)
{
	t_philo	*philo;
	t_base	*base;

	preprocessing(&base, &philo, argv);
	while (1)
	{
		pthread_mutex_lock(&base->complete_flag);
		if (philo->eat_cnt == 0)
			base->complete_eat_cnt++;
		if (base->complete_eat_cnt == base->num_of_philo)
		{
			pthread_mutex_unlock(&base->complete_flag);
			break ;
		}
		pthread_mutex_unlock(&base->complete_flag);
		pthread_mutex_lock(&base->finish_flag);
		if (base->finish)
		{
			pthread_mutex_unlock(&base->finish_flag);
			break ;
		}
		pthread_mutex_unlock(&base->finish_flag);
		routine(base, philo);
	}
	return (0);
}
