/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:44:07 by chiwon            #+#    #+#             */
/*   Updated: 2023/09/16 22:49:35 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int argc, char **argv)
{
    t_base      data;

    if (!argument_parsing(argc, argv, &data))
        return (0);
    start_routine(&data);
}