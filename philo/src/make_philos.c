/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:11:01 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/15 11:20:22 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_one(void *arg)
{
	t_philo *philo;
	t_time	time;
	long	start;

	philo = (t_philo *)arg;
	gettimeofday(&time, NULL);
	start = adj_time_form(&time);
	pthread_mutex_lock(philo->msg_mutex);
	printf("%ld %d is thinking\n", start, philo->num);
	pthread_mutex_unlock(philo->msg_mutex);
	while (1)
	{
		pthread_mutex_lock(philo->sts_mutex);
		if (philo->status == DEAD)
			return (NULL);
		pthread_mutex_unlock(philo->sts_mutex);
		usleep(100);
	}
}

static int	philo_one_case(t_env *env)
{
	if (pthread_create(&env->th[0], NULL, &philo_one, env->philos[0]))
		return (PTHREAD_ERROR);
	if (pthread_detach(env->th[0]))
		return (PTHREAD_ERROR);
	return (0);
}

int	event_start(t_philo **philos, t_env *env)
{
	int	i;

	env->th = (pthread_t *)malloc(sizeof(pthread_t) * (env->num_of_philos + 1));
	if (!env->th)
		return (MALLOC_ERROR);
	i = -1;
	while (env->num_of_philos > 1 && ++i < env->num_of_philos)
	{
		if (pthread_create(&env->th[i], NULL, &philo_event, philos[i]))
			return (PTHREAD_ERROR);
		if (pthread_detach(env->th[i]))
			return (PTHREAD_ERROR);
	}
	if (env->num_of_philos == 1)
	{
		if (philo_one_case(env))
			return (PTHREAD_ERROR);
		i += 2;
	}	
	if (pthread_create(&env->th[i], NULL, &monitor, env))
		return (PTHREAD_ERROR);
	if (pthread_join(env->th[i], NULL))
		return (PTHREAD_ERROR);
	return (0);
}
