/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:44:07 by chiwon            #+#    #+#             */
/*   Updated: 2023/09/24 14:42:38 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_finish(t_base *base)
{
	long long	save;
	int			i;

	i = 0;
	while (i < base->num_of_philo)
	{
		pthread_mutex_lock(&base->philo[i].last_eat_flag);
		if (get_millisec(base->philo[i].last_eat) >= base->time_to_die)
		{
			pthread_mutex_unlock(&base->philo[i].last_eat_flag);
			save = get_millisec(base->start);
			pthread_mutex_lock(&base->finish_flag);
			base->finish = 1;
			base->finish2 = 1;
			pthread_mutex_unlock(&base->finish_flag);
			pthread_mutex_unlock(&base->finish2_flag);
			printf("%lld %lld died\n", save, \
			base->philo[i].id + 1);
			return (0);
		}
		pthread_mutex_unlock(&base->philo[i].last_eat_flag);
		++i;
	}
	return (1);
}

void	monitoring(t_base *base)
{
	while (1)
	{
		pthread_mutex_lock(&base->complete_flag);
		if (base->complete_eat_cnt == base->num_of_philo)
		{
			pthread_mutex_unlock(&base->complete_flag);
			return ;
		}
		pthread_mutex_unlock(&base->complete_flag);
		pthread_mutex_lock(&base->finish2_flag);
		if (!check_finish(base))
			return ;
		pthread_mutex_unlock(&base->finish2_flag);
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	t_base	data;

	if (!argument_parsing(argc, argv, &data))
		return (0);
	start_routine(&data);
	if (data.philo != NULL)
		free(data.philo);
	if (data.tid != NULL)
		free(data.tid);
	if (data.forks != NULL)
		free(data.forks);
}
