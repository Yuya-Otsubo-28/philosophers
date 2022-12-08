/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:30:41 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/08 13:39:08 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int judge_msg(t_philo *philo, int status, long dis_time)
{
    if (status == FINISH)
        return (FINISH);
    else if (status == TAKE)
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
    return (NOTFIN);
}

static int dis_msg(t_philo *philo, int status)
{
    t_time time;
    int finornot;
    long dis_time;

    gettimeofday(&time, NULL);
    dis_time = adj_time_form(&time);
    pthread_mutex_lock(philo->sts_mutex);
    if (dis_time - philo->last_eat > philo->env->time_to_die)
    {
        dis_time = philo->last_eat + philo->env->time_to_die;
        philo->status = DEAD;
    }
    pthread_mutex_lock(philo->msg_mutex);
    finornot = judge_msg(philo, status, dis_time);
    pthread_mutex_unlock(philo->msg_mutex);
    pthread_mutex_unlock(philo->sts_mutex);
    return (finornot);
}

static int philo_odd(t_philo *philo)
{
    while (1)
    {
        if (dis_msg(philo, THINK) == FINISH)
            return (FINISH);
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
        pthread_mutex_unlock(&philo->left->fork);
        pthread_mutex_unlock(&philo->right->fork);
        usleep(philo->env->time_to_eat);
        if (dis_msg(philo, SLEEP) == FINISH)
            return (FINISH);
        usleep(philo->env->time_to_sleep);
    }
}

static int philo_even(t_philo *philo)
{
    while (1)
    {
        if (dis_msg(philo, THINK) == FINISH)
            return (FINISH);
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
        pthread_mutex_unlock(&philo->left->fork);
        pthread_mutex_unlock(&philo->right->fork);
        usleep(philo->env->time_to_eat);
        if (dis_msg(philo, SLEEP) == FINISH)
            return (FINISH);
        usleep(philo->env->time_to_sleep);
    }
}

void *philo_event(void *arg)
{
    t_philo *philo;

    puts("yeah");
	philo = (t_philo *)arg;
    if (philo->num % 2 == 1)
        philo_odd(philo);
    else
        philo_even(philo);
    return (NULL);
}
