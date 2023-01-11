/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:43:24 by yotsubo           #+#    #+#             */
/*   Updated: 2023/01/11 11:28:45 by yotsubo          ###   ########.fr       */
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
		printf("\x1b[34m%ld %d is sleeping\n\x1b[0m", philo->last_action, philo->num);
	else if (status == EAT)
	{
		philo->last_eat = philo->last_action;
		printf("\x1b[33m%ld %d is eating\n\x1b[0m", philo->last_action, philo->num);
		philo->eat_times++;
	}
	else if (status == THINK)
		printf("\x1b[32m%ld %d is thinking\n\x1b[0m", philo->last_action, philo->num);
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
