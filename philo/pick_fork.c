/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 02:29:44 by cahn              #+#    #+#             */
/*   Updated: 2023/09/18 02:41:55 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	take_rfork(t_philo *philo, t_base *base)
{
	int	rf;

	while (base->num_of_philo == 1)
	{
		pthread_mutex_lock(&base->dead_flag);
		if (base->dead)
		{
			pthread_mutex_unlock(&base->dead_flag);
			return (0);
		}
		pthread_mutex_unlock(&base->dead_flag);
	}
	rf = pthread_mutex_lock(philo->rfork);
	if (!rf && !print_state(get_millisec(base->start), philo->id + 1, \
		"has taken a fork", base))
	{
		pthread_mutex_unlock(philo->rfork);
		return (0);
	}
	return (1);
}

int	take_lfork(t_philo *philo, t_base *base)
{
	int	lf;

	lf = pthread_mutex_lock(philo->lfork);
	if (!lf && !print_state(get_millisec(base->start), philo->id + 1, \
		"has taken a fork", base))
	{
		pthread_mutex_unlock(philo->lfork);
		return (0);
	}
	return (1);
}

int	fork_controll(t_base *base, t_philo *philo)
{
	if (philo->id & 1)
	{
		if (!take_rfork(philo, base))
			return (0);
		if (!take_lfork(philo, base))
		{
			pthread_mutex_unlock(philo->rfork);
			return (0);
		}
	}
	else
	{
		if (!take_lfork(philo, base))
			return (0);
		if (!take_rfork(philo, base))
		{
			pthread_mutex_unlock(philo->lfork);
			return (0);
		}
	}
	return (1);
}
