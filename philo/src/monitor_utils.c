/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:41:53 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/19 13:36:04 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*set_fin_philos(t_env *env, int dead_philo)
{
	int	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		if (i != dead_philo)
			pthread_mutex_lock(&env->sts_mutexs[i]);
		env->philos[i].status = EAT;
		if (i != dead_philo)
			pthread_mutex_unlock(&env->sts_mutexs[i]);
		i++;
	}
	return (NULL);
}

void	unlock_all_sts(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_mutex_unlock(env->philos[i].sts_mutex);
		i++;
	}
}

void	lock_all_sts(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_mutex_lock(env->philos[i].sts_mutex);
		i++;
	}
}

int	inc_ach(t_env *env, int ach_num, int i)
{
	pthread_mutex_lock(env->philos[i].sts_mutex);
	if (env->philos[i].eat_times >= env->must_eat_num)
		ach_num++;
	pthread_mutex_unlock(env->philos[i].sts_mutex);
	return (ach_num);
}
