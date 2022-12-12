/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:11:01 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/12 09:46:02 by yotsubo          ###   ########.fr       */
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
    printf("%p\n", env);
    printf("%p\n", philos[1]->env);
    while (++i < env->num_of_philos)
    {
        printf("i; %d\n", i);
        pthread_create(&th[i], NULL, &philo_event, philos[i]);
    }
    pthread_create(&th[i], NULL, &monitor, env);
    pthread_join(th[i], NULL);
}
