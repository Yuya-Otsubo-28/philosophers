/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:30:41 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/14 15:44:17 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks_and_eat(t_philo *philo, long time_to_eat)
{
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
	usleep(time_to_eat * 1000);
	pthread_mutex_unlock(&philo->right->fork);
	pthread_mutex_unlock(&philo->left->fork);
	return (0);
}

static int	philo_odd(t_philo *philo)
{
	long	time_to_eat;
	long	time_to_sleep;

	time_to_eat = philo->env->time_to_eat;
	time_to_sleep = philo->env->time_to_sleep;
	while (1)
	{
		if (dis_msg(philo, THINK) == FINISH)
			return (FINISH);
		usleep((philo->env->time_to_die - time_to_eat - time_to_sleep) * 10);
		if (take_forks_and_eat(philo, time_to_eat) == FINISH)
			return (FINISH);
		if (dis_msg(philo, SLEEP) == FINISH)
			return (FINISH);
		usleep(time_to_sleep * 1000);
	}
}

static int	philo_even(t_philo *philo)
{
	long	time_to_eat;
	long	time_to_sleep;

	time_to_eat = philo->env->time_to_eat;
	time_to_sleep = philo->env->time_to_sleep;
	while (1)
	{
		if (dis_msg(philo, THINK) == FINISH)
			return (FINISH);
		usleep((philo->env->time_to_die - time_to_eat - time_to_sleep) * 10);
		if (take_forks_and_eat(philo, time_to_eat) == FINISH)
			return (FINISH);
		if (dis_msg(philo, SLEEP) == FINISH)
			return (FINISH);
		usleep(time_to_sleep * 1000);
	}
}

void	*philo_event(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 == 1)
	{
		usleep(500);
		philo_odd(philo);
	}
	else
		philo_even(philo);
	return (NULL);
}
