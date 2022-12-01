/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:11:01 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/01 17:56:11 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void event_start(t_philo **philos, t_env *env)
{
    int i;
    pthread_t *th;

    th = (pthread_t *)malloc(sizeof(pthread_t) * env->num_of_philos);
    /*
    if (!th)
        return ;
    */
    i = -1;
    while (++i < env->num_of_philos)
        pthread_create(&th[i], NULL, &philo_event, philos[i]);
    printf("i ; %d\n", i);
    pthread_create(&th[i], NULL, &monitor, env);
    pthread_join(th[i], NULL);
}