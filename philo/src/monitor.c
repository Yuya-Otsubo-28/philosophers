/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:44:42 by yotsubo           #+#    #+#             */
/*   Updated: 2023/02/18 17:09:56 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_info *info, int i)
{
	long	now;
	long	tmp;
	long	last_eat;

	tmp = 0;
	now = get_time();
	pthread_mutex_lock(&info->sts_mutexs[i]);
	last_eat = info->philos[i].last_eat;
	pthread_mutex_unlock(&info->sts_mutexs[i]);
	if (last_eat != NOTSET)
		tmp = now - last_eat;
	if (tmp > info->time_to_die)
	{
		pthread_mutex_lock(&info->msg_mutex);
		lock_all_sts(info);
		now = get_time() - info->start_time;
		printf("\x1b[31m%ld %d died\n\x1b[0m", now, info->philos[i].num);
		info->fin = FINISH;
		unlock_all_sts(info);
		pthread_mutex_unlock(&info->msg_mutex);
		return (FINISH);
	}
	return (0);
}

static int	check_count(t_info *info, int ach_num)
{
	if (ach_num == info->num_of_philos)
	{
		pthread_mutex_lock(&info->msg_mutex);
		set_fin_philos(info, NOTSET);
		pthread_mutex_unlock(&info->msg_mutex);
		return (FINISH);
	}
	return (0);
}

void	*monitor(void *arg)
{
	int			i;
	int			ach_num;
	t_info		*info;

	info = (t_info *)arg;
	while (1)
	{
		ach_num = 0;
		i = 0;
		while (i < info->num_of_philos)
		{
			if (check_death(info, i) == FINISH)
				return (NULL);
			if (info->must_eat_num != NOTSET)
				ach_num = inc_ach(info, ach_num, i);
			i++;
		}
		if (check_count(info, ach_num) == FINISH)
			return (NULL);
	}
}
