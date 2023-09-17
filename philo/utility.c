/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiwon <chiwon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:29:33 by chiwon            #+#    #+#             */
/*   Updated: 2023/09/17 18:28:09 by chiwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atol(const char *str)
{
	int	        minus;
	int	        i;
	long long   num;

	i = 0;
	minus = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	return (num * minus);
}

long long	get_millisec(struct timeval start)
{
	struct timeval  end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec - start.tv_sec) * 1000 + \
			(end.tv_usec - start.tv_usec) / 1000);
}

int	print_state(long long time, long long id, char *message, t_base *base)
{
	pthread_mutex_lock(&base->dead_flag);
	if (base->dead)
	{
		pthread_mutex_unlock(&base->dead_flag);
		return (0);
	}
	pthread_mutex_unlock(&base->dead_flag);
	printf("%lld %lld %s\n", time, id, message);
	return (1);
}

void	mysleep(long long millisec)
{
	long long		cur;
	struct timeval 	cur_t;

	cur = 0;
	gettimeofday(&cur_t, NULL);
	while (cur < millisec)
	{
		usleep(500);
		cur = get_millisec(cur_t);
	}
}

void	destroy_mutex(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->num_of_philo)
	{
		pthread_mutex_destroy(&base->forks[i]);
		++i;
	}
	pthread_mutex_destroy(&base->exclude_flag);
	pthread_mutex_destroy(&base->dead_flag);
	pthread_mutex_destroy(&base->complete_flag);
}