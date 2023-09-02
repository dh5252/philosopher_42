/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiwon <chiwon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:44:07 by chiwon            #+#    #+#             */
/*   Updated: 2023/09/02 22:29:24 by chiwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int argc, char **argv)
{
    t_base      data;
    pthread_t   thread;

    if (!argument_parsing(argc, argv, &data))
        return (0);
    //if (pthread_create(&thread, NULL))
}