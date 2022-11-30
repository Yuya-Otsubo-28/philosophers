/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:11:01 by yotsubo           #+#    #+#             */
/*   Updated: 2022/11/30 12:40:37 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int dis_msg(pthread_t *philo, int status)
{
    t_time time;
    long dis_time;

    gettimeofday(&time, NULL);
    dis_time = adj_time_form(&time);
    if (judge_finish(philo->env) == FINISH)
        return (FINISH);
    pthread_mutex_lock(philo->msg);
    if (status == TAKE)
        printf("%ld %d has taken a fork\n", dis_time, num);
    else if (status == SLEEP)
        printf("%ld %d is sleeping\n", dis_time, num);
    else if (status == EAT)
        printf("%ld %d is eating\n", dis_time, num);
    else if (status == THINK)
        printf("%ld %d is thinking\n", dis_time, num);
    else if (status == DEAD)
        printf("%ld %d died\n", dis_time, num)
    pthread_mutex_unlock(philo->msg);
    return (0);
}

void philo_odd(t_philo *philo)
{
    while (1)
    {
        pthread_mutex_lock(philo->left);
        if (dis_msg(philo, TAKE) == FINISH)
        {
            pthread_mutex_unlock(philo->left);
            return ;
        }
        pthread_mutex_lock(philo->right);
        if (dis_msg(philo, TAKE) == FINISH)
        {
            pthread_mutex_unlock(philo->left);
            pthread_mutex_unlock(philo->right);
            return ;
        }

        pthread_mutex_unlock(philo->left);
        pthread_mutex_unlock(philo->right);
    }
}

void *philo_event(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->num % 2 == 1)
        philo_odd(philo);
    else
        philo_even(philo);
}


void make_philos(t_philo **philos, t_env *env)
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
}