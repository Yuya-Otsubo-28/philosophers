/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:05:17 by yotsubo           #+#    #+#             */
/*   Updated: 2023/02/18 17:19:01 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(int argc, char *argv[], t_info *info, t_time *time)
{
	info->num_of_philos = ph_atoi(argv[1]);
	info->time_to_die = ph_atoi(argv[2]);
	info->time_to_eat = ph_atoi(argv[3]);
	info->time_to_sleep = ph_atoi(argv[4]);
	info->next_philo_num = 0;
	pthread_mutex_init(&info->msg_mutex, NULL);
	pthread_mutex_init(&info->num_mutex, NULL);
	if (info->num_of_philos == NOTSET || info->time_to_die == NOTSET
		|| info->time_to_eat == NOTSET || info->time_to_sleep == NOTSET
		|| info->num_of_philos >= MAX_NUM)
		return (ARGS_ERROR);
	if (gettimeofday(time, NULL) == -1)
		return (TIME_ERROR);
	if (argc == ADDED_ARGS_NUM)
	{
		info->must_eat_num = ph_atoi(argv[5]);
		if (info->must_eat_num == NOTSET)
			return (ARGS_ERROR);
	}
	else
		info->must_eat_num = NOTSET;
	info->fin = NOTSET;
	if (init_sts(info))
		return (PTHREAD_ERROR);
	return (0);
}

static int	init_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (PTHREAD_ERROR);
		i++;
	}
	return (0);
}

static int	init_member(int i, t_philo *philo, t_info *info)
{
	philo->info = info;
	philo->msg_mutex = &info->msg_mutex;
	philo->sts_mutex = &info->sts_mutexs[i];
	philo->status = NOTSET;
	philo->num = i + 1;
	philo->last_eat = NOTSET;
	philo->last_action = 0;
	philo->eat_times = 0;
	return (0);
}

static int	init_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		init_member(i, &info->philos[i], info);
		i++;
	}
	return (0);
}

int	init_philo_fork(t_info *info)
{
	if (init_forks(info))
	{
		error_handler(PTHREAD_ERROR);
		return (PTHREAD_ERROR);
	}
	init_philos(info);
	return (0);
}
