/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:30:41 by yotsubo           #+#    #+#             */
/*   Updated: 2023/02/18 17:25:27 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks_and_eat_e(t_philo *philo, long time_to_eat)
{
	pthread_mutex_lock(&philo->info->forks[philo->left]);
	if (dis_msg(philo, TAKE, 0) == FINISH)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->left]);
		return (FINISH);
	}
	pthread_mutex_lock(&philo->info->forks[philo->right]);
	if (dis_msg(philo, TAKE, 0) == FINISH)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->right]);
		pthread_mutex_unlock(&philo->info->forks[philo->left]);
		return (FINISH);
	}
	if (dis_msg(philo, EAT, time_to_eat) == FINISH)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->right]);
		pthread_mutex_unlock(&philo->info->forks[philo->left]);
		return (FINISH);
	}
	pthread_mutex_unlock(&philo->info->forks[philo->left]);
	pthread_mutex_unlock(&philo->info->forks[philo->right]);
	return (0);
}

static int	take_forks_and_eat_o(t_philo *philo, long time_to_eat)
{
	pthread_mutex_lock(&philo->info->forks[philo->right]);
	if (dis_msg(philo, TAKE, 0) == FINISH)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->right]);
		return (FINISH);
	}
	pthread_mutex_lock(&philo->info->forks[philo->left]);
	if (dis_msg(philo, TAKE, 0) == FINISH)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->right]);
		pthread_mutex_unlock(&philo->info->forks[philo->left]);
		return (FINISH);
	}
	if (dis_msg(philo, EAT, time_to_eat) == FINISH)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->right]);
		pthread_mutex_unlock(&philo->info->forks[philo->left]);
		return (FINISH);
	}
	pthread_mutex_unlock(&philo->info->forks[philo->right]);
	pthread_mutex_unlock(&philo->info->forks[philo->left]);
	return (0);
}

static int	philo_life_o(t_philo *philo)
{
	int	time_to_eat;
	int	time_to_sleep;

	time_to_eat = philo->info->time_to_eat;
	time_to_sleep = philo->info->time_to_sleep;
	while (1)
	{
		if (take_forks_and_eat_o(philo, time_to_eat) == FINISH)
			return (FINISH);
		if (dis_msg(philo, SLEEP, time_to_sleep) == FINISH)
			return (FINISH);
		if (dis_msg(philo, THINK, 0) == FINISH)
			return (FINISH);
	}
}

static int	philo_life_e(t_philo *philo)
{
	int	time_to_eat;
	int	time_to_sleep;

	time_to_eat = philo->info->time_to_eat;
	time_to_sleep = philo->info->time_to_sleep;
	while (1)
	{
		if (take_forks_and_eat_e(philo, time_to_eat) == FINISH)
			return (FINISH);
		if (dis_msg(philo, SLEEP, time_to_sleep) == FINISH)
			return (FINISH);
		if (dis_msg(philo, THINK, 0) == FINISH)
			return (FINISH);
	}
}

void	*philo_event(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->info->num_mutex);
	philo->info->next_philo_num += 2;
	philo->num = philo->info->next_philo_num;
	if (philo->info->next_philo_num == philo->info->num_of_philos
		|| philo->info->next_philo_num == philo->info->num_of_philos - 1)
		philo->info->next_philo_num = -1;
	pthread_mutex_unlock(&philo->info->num_mutex);
	philo->right = philo->num - 1;
	if (philo->num == 1)
		philo->left = philo->info->num_of_philos - 1;
	else
		philo->left = philo->num - 2;
	if (philo->num % 2 == 0)
		philo_life_e(philo);
	else
	{
		dis_msg(philo, THINK, 0);
		philo_life_o(philo);
	}
	return (NULL);
}
