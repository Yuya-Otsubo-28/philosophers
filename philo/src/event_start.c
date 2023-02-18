/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:11:01 by yotsubo           #+#    #+#             */
/*   Updated: 2023/02/18 12:48:58 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_one(void *arg)
{
	t_philo	*philo;
	long	start;

	philo = (t_philo *)arg;
	start = 0;
	printf("%ld %d is taking a fork\n", start, philo->num);
	pthread_mutex_lock(philo->sts_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->sts_mutex);
	while (1)
	{
		pthread_mutex_lock(philo->msg_mutex);
		if (philo->info->fin == FINISH)
		{
			pthread_mutex_unlock(philo->msg_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(philo->msg_mutex);
	}
}

static int	philo_one_case(t_info *info)
{
	info->start_time = get_time();
	if (pthread_create(&info->th[0], NULL, &philo_one, &info->philos[0]))
		return (PTHREAD_ERROR);
	if (pthread_detach(info->th[0]))
		return (PTHREAD_ERROR);
	if (pthread_create(&info->th[1], NULL, &monitor, info))
		return (PTHREAD_ERROR);
	if (pthread_join(info->th[1], NULL))
		return (PTHREAD_ERROR);
	return (0);
}

static int	make_philos(t_info *info)
{
	int	i;

	i = 0;
	info->start_time = get_time();
	while (i < info->num_of_philos)
	{
		if (pthread_create(&info->th[i], NULL, &philo_event, &info->philos[i]))
			return (PTHREAD_ERROR);
		i++;
	}
	return (0);
}

int	event_start(t_info *info)
{
	int	i;

	if (info->num_of_philos == 1)
	{
		if (philo_one_case(info))
			return (PTHREAD_ERROR);
		return (0);
	}
	if (make_philos(info))
		return (PTHREAD_ERROR);
	if (pthread_create(&info->th[info->num_of_philos], NULL, &monitor, info))
		return (PTHREAD_ERROR);
	if (pthread_join(info->th[info->num_of_philos], NULL))
		return (PTHREAD_ERROR);
	i = 0;
	while (i < info->num_of_philos)
	{
		if (pthread_join(info->th[i], NULL))
			return (PTHREAD_ERROR);
		i++;
	}
	return (0);
}
