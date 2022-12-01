/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:44:42 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/01 17:39:23 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *set_fin_philos(t_env *env, int dead_num)
{
    int i;

    i = 0;
    while (i < env->num_of_philos)
    {
        if (i != dead_num)
            pthread_mutex_lock(env->philos[i]->sts_mutex);
        env->philos[i]->status = FINISH;
        if (i != dead_num)
            pthread_mutex_unlock(env->philos[i]->sts_mutex);
        i++;
    }
    return (NULL);
}

void *monitor(void *arg)
{
    int i;
    int ach_num;
    t_env *env;

    env = (t_env *)arg;
    while (1)
    {
        ach_num = 0;
        i = 0;
        while (i < env->num_of_philos)
        {
            pthread_mutex_lock(env->philos[i]->sts_mutex);
            if (env->philos[i]->status == DEAD)
                return (set_fin_philos(env, i));
            if (env->must_eat_num != NOTSET)
            {
                if (env->philos[i]->eat_times == env->must_eat_num)
                    ach_num++;
            }
            pthread_mutex_unlock(env->philos[i]->sts_mutex);
            i++;
        }
        if (ach_num == env->num_of_philos)
            return (set_fin_philos(env, NOTSET));
    }
}