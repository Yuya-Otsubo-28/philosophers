/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:30:41 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/12 15:29:22 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int judge_msg(t_philo *philo, int status, long dis_time)
{
    pthread_mutex_lock(philo->sts_mutex);
    if (philo->status == DEAD || philo->status == FINISH)
        return (FINISH);
    else if (status == TAKE)
        printf("%ld %d has taken a fork\n", dis_time, philo->num);
    else if (status == SLEEP)
        printf("%ld %d is sleeping\n", dis_time, philo->num);
    else if (status == EAT)
    {
        philo->last_eat = dis_time;
        printf("%ld %d is eating\n", dis_time, philo->num);
        philo->eat_times++;
    }
    else if (status == THINK)
        printf("%ld %d is thinking\n", dis_time, philo->num);
    pthread_mutex_unlock(philo->sts_mutex);
    return (NOTFIN);
}

static int dis_msg(t_philo *philo, int status)
{
    t_time time;
    int finornot;
    long dis_time;

    finornot = FINISH;
    pthread_mutex_lock(philo->msg_mutex);
    gettimeofday(&time, NULL);
    dis_time = adj_time_form(&time);
    finornot = judge_msg(philo, status, dis_time);
    pthread_mutex_unlock(philo->msg_mutex);
    return (finornot);
}

static int philo_odd(t_philo *philo)
{
    long time_to_eat;
    long time_to_sleep;

    time_to_eat = philo->env->time_to_eat;
    time_to_sleep = philo->env->time_to_sleep;
    while (1)
    {
        if (dis_msg(philo, THINK) == FINISH)
            return (FINISH);
        usleep(200);
        pthread_mutex_lock(&philo->left->fork);
        if (dis_msg(philo, TAKE) == FINISH)
        {
            pthread_mutex_unlock(&philo->left->fork);
            return (FINISH);
        }
        pthread_mutex_lock(&philo->right->fork);
        if (dis_msg(philo, TAKE) == FINISH)
        {
            pthread_mutex_unlock(&philo->left->fork);
            pthread_mutex_unlock(&philo->right->fork);
            return (FINISH);
        }
        if (dis_msg(philo, EAT) == FINISH)
        {
            pthread_mutex_unlock(&philo->left->fork);
            pthread_mutex_unlock(&philo->right->fork);
            return (FINISH);
        }
		usleep(time_to_eat * 1000);
        pthread_mutex_unlock(&philo->left->fork);
        pthread_mutex_unlock(&philo->right->fork);
        if (dis_msg(philo, SLEEP) == FINISH)
            return (FINISH);
        usleep(time_to_sleep * 1000);
    }
}

static int philo_even(t_philo *philo)
{
    long time_to_eat;
    long time_to_sleep;

    time_to_eat = philo->env->time_to_eat;
    time_to_sleep = philo->env->time_to_sleep;
    while (1)
    {
        if (dis_msg(philo, THINK) == FINISH)
            return (FINISH);
        usleep(150);
        pthread_mutex_lock(&philo->right->fork);
        if (dis_msg(philo, TAKE) == FINISH)
        {
            pthread_mutex_unlock(&philo->right->fork);
            return (FINISH);
        }
        pthread_mutex_lock(&philo->left->fork);
        if (dis_msg(philo, TAKE) == FINISH)
        {
            pthread_mutex_unlock(&philo->right->fork);
            pthread_mutex_unlock(&philo->left->fork);
            return (FINISH);
        }
        if (dis_msg(philo, EAT) == FINISH)
        {
            pthread_mutex_unlock(&philo->left->fork);
            pthread_mutex_unlock(&philo->right->fork);
            return (FINISH);
        }
		usleep(time_to_eat * 1000);
        pthread_mutex_unlock(&philo->left->fork);
        pthread_mutex_unlock(&philo->right->fork);
        if (dis_msg(philo, SLEEP) == FINISH)
            return (FINISH);
        usleep(time_to_sleep * 1000);
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
    return (NULL);
}
