/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:06:56 by cahn              #+#    #+#             */
/*   Updated: 2023/09/24 14:55:56 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	start_routine(t_base *base)
{
	int	i;

	i = 0;
	pthread_mutex_init(&base->finish2_flag, NULL);
	pthread_mutex_init(&base->complete_flag, NULL);
	pthread_mutex_init(&base->finish_flag, NULL);
	gettimeofday(&base->start, NULL);
	base->finish2 = 0;
	while (i < base->num_of_philo)
	{
		base->philo[i].last_eat = base->start;
		if (pthread_create(&base->tid[i], NULL, scheduling, &base->philo[i]))
			return ;
		++i;
	}
	if (base->time_to_die != 0 && base->min_eat_cnt != 0)
		monitoring(base);
	i = 0;
	while (i < base->num_of_philo)
		pthread_join(base->tid[i++], NULL);
	destroy_mutex(base);
}

int	routine(t_base *base, t_philo *philo)
{
	if (!fork_controll(base, philo))
		return (0);
	if (!eating(base, philo))
		return (0);
	if (!sleeping(base, philo))
		return (0);
	usleep(1000);
	if (!print_state_with_finish(get_millisec(base->start), \
		philo->id + 1, "is thinking", base))
		return (0);
	return (1);
}

int	preprocessing(t_base **base, t_philo **philo, void *argv)
{
	*philo = (t_philo *)argv;
	*base = (*philo)->base;
	if ((*base)->time_to_die == 0)
	{
		if ((*philo)->id == 0)
			printf("0 1 died\n");
		return (0);
	}
	if ((*base)->min_eat_cnt == 0)
		return (0);
	if ((*philo)->id & 1)
		usleep(20);
	if (((*base)->num_of_philo & 1) && (*philo)->id == 0)
		usleep(100);
	return (1);
}

void	*scheduling(void *argv)
{
	t_philo	*philo;
	t_base	*base;

	if (!preprocessing(&base, &philo, argv))
		return (0);
	while (routine(base, philo))
	{
	}
	return (0);
}
