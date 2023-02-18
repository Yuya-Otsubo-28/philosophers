/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:43:24 by yotsubo           #+#    #+#             */
/*   Updated: 2023/02/18 17:18:23 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*judge_msg(int status)
{
	if (status == TAKE)
		return ("has taken a fork\n");
	if (status == SLEEP)
		return ("is sleeping\n");
	if (status == THINK)
		return ("is thinking\n");
	else
		return (NULL);
}

static int	display_msg(t_philo *philo, int status)
{
	char	*template;

	template = judge_msg(status);
	philo->last_action = get_time() - philo->info->start_time;
	pthread_mutex_lock(philo->msg_mutex);
	if (philo->info->fin == FINISH)
	{
		pthread_mutex_unlock(philo->msg_mutex);
		return (FINISH);
	}
	if (status == EAT)
	{
		pthread_mutex_lock(philo->sts_mutex);
		philo->last_eat = get_time();
		printf("\x1b[33m%ld %d is eating\n\x1b[0m",
			philo->last_action, philo->num);
		philo->eat_times++;
		pthread_mutex_unlock(philo->sts_mutex);
	}
	else
		printf("%ld %d %s", philo->last_action, philo->num, template);
	pthread_mutex_unlock(philo->msg_mutex);
	return (NOTFIN);
}

int	dis_msg(t_philo *philo, int status, long sleep_time)
{
	int		finornot;

	finornot = display_msg(philo, status);
	usleep(sleep_time * 1000);
	return (finornot);
}
