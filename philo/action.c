/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:24:00 by cahn              #+#    #+#             */
/*   Updated: 2023/09/24 01:06:14 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	sleeping(t_base *base, t_philo *philo)
{
	if (!print_state_with_finish(get_millisec(base->start), philo->id + 1, \
				"is sleeping", base))
		return (0);
	mysleep(base->time_to_sleep);
	return (1);
}

void	update_eat_and_fork(t_base *base, t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat_flag);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(&philo->last_eat_flag);
	mysleep(base->time_to_eat);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

void	update_finish(t_base *base)
{
	base->finish = 1;
	pthread_mutex_lock(&base->finish2_flag);
	base->finish2 = 1;
	pthread_mutex_unlock(&base->finish2_flag);
	pthread_mutex_unlock(&base->complete_flag);
	pthread_mutex_unlock(&base->finish_flag);
}

int	eating(t_base *base, t_philo *philo)
{
	pthread_mutex_lock(&base->finish_flag);
	if (base->finish)
	{
		pthread_mutex_unlock(&base->finish_flag);
		return (0);
	}
	printf("%lld %lld is eating\n", get_millisec(base->start), philo->id + 1);
	philo->eat_cnt--;
	if (philo->eat_cnt == 0)
	{
		pthread_mutex_lock(&base->complete_flag);
		base->complete_eat_cnt++;
		if (base->complete_eat_cnt == base->num_of_philo)
		{
			update_finish(base);
			return (0);
		}
		pthread_mutex_unlock(&base->complete_flag);
	}
	pthread_mutex_unlock(&base->finish_flag);
	update_eat_and_fork(base, philo);
	return (1);
}
