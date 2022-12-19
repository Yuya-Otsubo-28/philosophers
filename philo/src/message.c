/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:43:24 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/19 13:35:30 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	judge_msg(t_philo *philo, int status)
{
	pthread_mutex_lock(philo->msg_mutex);
	philo->last_action = get_time();
	pthread_mutex_lock(philo->sts_mutex);
	if (philo->env->fin == FINISH)
		return (FINISH);
	else if (status == TAKE)
		printf("%ld %d has taken a fork\n", philo->last_action, philo->num);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", philo->last_action, philo->num);
	else if (status == EAT)
	{
		philo->last_eat = philo->last_action;
		printf("%ld %d is eating\n", philo->last_action, philo->num);
		philo->eat_times++;
	}
	else if (status == THINK)
		printf("%ld %d is thinking\n", philo->last_action, philo->num);
	pthread_mutex_unlock(philo->sts_mutex);
	pthread_mutex_unlock(philo->msg_mutex);
	return (NOTFIN);
}

int	dis_msg(t_philo *philo, int status, long sleep_time)
{
	int		finornot;

	finornot = judge_msg(philo, status);
	if (status == THINK)
		mod_usleep(sleep_time / 1000);
	else
		mod_usleep(sleep_time);
	philo->last_action = get_time();
	return (finornot);
}
