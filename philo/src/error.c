/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:05:50 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/01 13:37:22 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_philos(t_philo **philos, int num_of_philos)
{
    int i;

    i = 0;
    while (i < num_of_philos)
        free(philos[i++]);
    free(philos);
}

void destroy_sts(pthread_mutex_t *sts_mutex, int num_of_philos)
{
    int i;

    i = 0;
    while (i < num_of_philos)
        pthread_mutex_destroy(&sts_mutex[i++]);
    free(sts_mutex);
}

void destroy_forks(t_fork **forks, int num_of_forks)
{
    int i;

    i = 0;
    while (i < num_of_forks)
    {
        pthread_mutex_destroy(forks[i]->fork);
        free(forks[i]);
        i++;
    }
    free(forks);
}

int error_handler(int error_num)
{
    if (error_num == ARGS_ERROR)
        ft_putstr_fd("*** ARGUMENT ERROR ***\n", STDERR_FILENO);
    if (error_num == MALLOC_ERROR)
        ft_putstr_fd("*** MALLOC ERROR ***\n", STDERR_FILENO);
    return (-1);
}