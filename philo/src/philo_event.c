/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:30:41 by yotsubo           #+#    #+#             */
/*   Updated: 2022/11/30 16:49:55 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void judge_msg(t_philo *philo, int status, long dis_time)
{
    if (status == TAKE)
        printf("%ld %d has taken a fork\n", dis_time, philo->num);
    else if (status == SLEEP)
        printf("%ld %d is sleeping\n", dis_time, philo->num);
    else if (status == EAT)
    {
        philo->last_eat = dis_time;
        printf("%ld %d is eating\n", dis_time, philo->num);
    }
    else if (status == THINK)
        printf("%ld %d is thinking\n", dis_time, philo->num);
    else if (status == DEAD)
        printf("%ld %d died\n", dis_time, philo->num);
}

int dis_msg(t_philo *philo, int status)
{
    t_time time;
    long dis_time;

    gettimeofday(&time, NULL);
    dis_time = adj_time_form(&time);
    if (judge_finish(philo->env) == FINISH)
        return (FINISH);
    pthread_mutex_lock(philo->sts_mutex);
    if (dis_time - philo->last_eat > philo->env->time_to_die)
    {
        dis_time = philo->last_eat + philo->env->time_to_die;
        philo->status = DEAD;
    }
    pthread_mutex_lock(philo->msg_mutex);
    judge_msg(philo, status, dis_time);
    pthread_mutex_unlock(philo->msg_mutex);
    pthread_mutex_unlock(philo->sts_mutex);
    return (0);
}

int philo_odd(t_philo *philo)
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
        dis_msg(philo, EAT);
        pthread_mutex_unlock(philo->left);
        pthread_mutex_unlock(philo->right);
        usleep(philo->env->time_to_eat);
        dis_msg(philo, SLEEP);
        usleep(philo->env->time_to_sleep);
    }
}

int philo_even(t_philo *philo)
{
    while (1)
    {
        pthread_mutex_lock(philo->right);
        if (dis_msg(philo, TAKE) == FINISH)
        {
            pthread_mutex_unlock(philo->right);
            return ;
        }
        pthread_mutex_lock(philo->left);
        if (dis_msg(philo, TAKE) == FINISH)
        {
            pthread_mutex_unlock(philo->right);
            pthread_mutex_unlock(philo->left);
            return ;
        }
        dis_msg(philo, EAT);
        pthread_mutex_unlock(philo->right);
        pthread_mutex_unlock(philo->left);
        usleep(philo->env->time_to_eat);
        dis_msg(philo, SLEEP);
        usleep(philo->env->time_to_sleep);
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