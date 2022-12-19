/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:30:41 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/19 11:05:39 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks_and_eat_e(t_philo *philo, long time_to_eat)
{
	pthread_mutex_lock(&philo->right->fork);
	if (dis_msg(philo, TAKE, 0) == FINISH)
	{
		pthread_mutex_unlock(&philo->right->fork);
		return (FINISH);
	}
	pthread_mutex_lock(&philo->left->fork);
	if (dis_msg(philo, TAKE, 0) == FINISH)
	{
		pthread_mutex_unlock(&philo->right->fork);
		pthread_mutex_unlock(&philo->left->fork);
		return (FINISH);
	}
	if (dis_msg(philo, EAT, time_to_eat) == FINISH)
	{
		pthread_mutex_unlock(&philo->right->fork);
		pthread_mutex_unlock(&philo->left->fork);
		return (FINISH);
	}
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->right->fork);
	return (0);
}

static int	take_forks_and_eat_o(t_philo *philo, long time_to_eat)
{
	pthread_mutex_lock(&philo->left->fork);
	if (dis_msg(philo, TAKE, 0) == FINISH)
	{
		pthread_mutex_unlock(&philo->left->fork);
		return (FINISH);
	}
	pthread_mutex_lock(&philo->right->fork);
	if (dis_msg(philo, TAKE, 0) == FINISH)
	{
		pthread_mutex_unlock(&philo->left->fork);
		pthread_mutex_unlock(&philo->right->fork);
		return (FINISH);
	}
	if (dis_msg(philo, EAT, time_to_eat) == FINISH)
	{
		pthread_mutex_unlock(&philo->left->fork);
		pthread_mutex_unlock(&philo->right->fork);
		return (FINISH);
	}
	pthread_mutex_unlock(&philo->right->fork);
	pthread_mutex_unlock(&philo->left->fork);
	return (0);
}

static int	philo_odd(t_philo *philo)
{
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_die;
	int	time_to_think;

	time_to_eat = philo->env->time_to_eat;
	time_to_sleep = philo->env->time_to_sleep;
	time_to_die = philo->env->time_to_die;
	printf("%d : %ld\n", philo->num, get_time());
	if (time_to_die > time_to_eat + time_to_sleep)
		time_to_think = time_to_die - time_to_eat - time_to_sleep;
	else
		time_to_think = 50;
	while (1)
	{
		if (dis_msg(philo, THINK, time_to_think) == FINISH)
			return (FINISH);
		if (take_forks_and_eat_o(philo, time_to_eat) == FINISH)
			return (FINISH);
		if (dis_msg(philo, SLEEP, time_to_sleep) == FINISH)
			return (FINISH);
	}
}

static int	philo_even(t_philo *philo)
{
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_die;
	int	time_to_think;

	time_to_eat = philo->env->time_to_eat;
	time_to_sleep = philo->env->time_to_sleep;
	time_to_die = philo->env->time_to_die;
	printf("%d : %ld\n", philo->num, get_time());
	if (time_to_die > time_to_eat + time_to_sleep)
		time_to_think = time_to_die - time_to_eat - time_to_sleep;
	else
		time_to_think = 50;
	while (1)
	{
		if (dis_msg(philo, THINK, time_to_think) == FINISH)
			return (FINISH);
		if (take_forks_and_eat_e(philo, time_to_eat) == FINISH)
			return (FINISH);
		if (dis_msg(philo, SLEEP, time_to_sleep) == FINISH)
			return (FINISH);
	}
}

void	*philo_event(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->sts_mutex);
	philo->status = START;
	pthread_mutex_unlock(philo->sts_mutex);
	while (1)
	{
		pthread_mutex_lock(philo->sts_mutex);
		if (philo->status == GO)
		{
			pthread_mutex_unlock(philo->sts_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->sts_mutex);
		mod_usleep(1);
	}
	printf("%d : %ld\n", philo->num, get_time());
	if (philo->num % 2 == 1)
	{
		mod_usleep(philo->env->time_to_eat);
		if (philo->num == 1)
			philo_even(philo);
		else
			philo_odd(philo);
	}
	else
		philo_even(philo);
	return (NULL);
}

// struct timeval	time;
// long			start;
// gettimeofday(&time, NULL);
// start = adj_time_form(&time);
// printf("%d : %ld\n", philo->num, start);