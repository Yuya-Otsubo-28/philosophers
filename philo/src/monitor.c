/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:44:42 by yotsubo           #+#    #+#             */
/*   Updated: 2022/11/30 12:56:41 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int judge_finish(t_env *env)
{
    int i;
    int ach_num;

    ach_num = 0;
    i = 0;
    while (i < env->num_of_philos)
    {
        if (env->philos[i]->status == DEAD)
            return (FINISH);
        if (env->must_eat_num != NOTSET)
        {
            if (env->philos[i]->eat_times == env->must_eat_num)
                ach_num++;
        }
        i++;
    }
    if (ach_num == env->num_of_philos)
        return (FINISH);
    else
        return (NOTFIN)
}