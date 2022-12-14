/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:43:24 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/15 07:58:10 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	judge_msg(t_philo *philo, int status, long dis_time)
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

int	dis_msg(t_philo *philo, int status)
{
	t_time	time;
	int		finornot;
	long	dis_time;

	pthread_mutex_lock(philo->msg_mutex);
	gettimeofday(&time, NULL);
	dis_time = adj_time_form(&time);
	finornot = judge_msg(philo, status, dis_time);
	pthread_mutex_unlock(philo->msg_mutex); 
	return (finornot);
}
