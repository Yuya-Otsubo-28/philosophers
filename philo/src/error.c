/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:05:50 by yotsubo           #+#    #+#             */
/*   Updated: 2022/11/30 10:05:51 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void destroy_forks(t_fork *forks, int num_of_forks)
{
    int i;

    i = 0;
    while (i < num_of_forks)
    {
        pthread_mutex_destroy(forks[i].fork);
        i++;
    }
}

void error_handler(int error_num)
{
    if (error_num == ARGS_ERROR)
        ft_putstr_fd("*** ARGUMENT ERROR ***/n", STDERR_FILENO);
    if (error_num == MALLOC_ERROR)
        ft_putstr_fd("*** MALLOC ERROR ***/n", STDERR_FILENO);
    exit(1);
}