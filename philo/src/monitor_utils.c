/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:41:53 by yotsubo           #+#    #+#             */
/*   Updated: 2023/02/18 10:43:24 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*set_fin_philos(t_info *info, int dead_philo)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		if (i != dead_philo)
			pthread_mutex_lock(&info->sts_mutexs[i]);
		info->fin = FINISH;
		if (i != dead_philo)
			pthread_mutex_unlock(&info->sts_mutexs[i]);
		i++;
	}
	return (NULL);
}

void	unlock_all_sts(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_mutex_unlock(info->philos[i].sts_mutex);
		i++;
	}
}

void	lock_all_sts(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_mutex_lock(info->philos[i].sts_mutex);
		i++;
	}
}

int	inc_ach(t_info *info, int ach_num, int i)
{
	pthread_mutex_lock(info->philos[i].sts_mutex);
	if (info->philos[i].eat_times >= info->must_eat_num)
		ach_num++;
	pthread_mutex_unlock(info->philos[i].sts_mutex);
	return (ach_num);
}
