/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiwon <chiwon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:29:33 by chiwon            #+#    #+#             */
/*   Updated: 2023/09/02 15:53:18 by chiwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(const char *str)
{
	int	minus;
	int	i;
	int	num;

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

int argument_valid(const char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9)'))
            return (0);
        ++i;
    }
    return (1);
}

int argument_parsing(int argc, char **argv, t_philo *philo)
{
    int i;

    if (!(argc == 5 || argc == 6))
    {
        printf("argument number error\n");
        return (0);
    }
    i = 1;
    while (argv[i])
    {
        if (argument_valid(argv[i]))
            philo->argv[i - 1] = ft_atoi(argv[i]);
        else
        {
            printf("argument value error\n");
            return (0);
        }
        ++i;
    }
    if (argc == 5)
        philo->argv[LIMIT_EAT] = -1;
    return (1);
}