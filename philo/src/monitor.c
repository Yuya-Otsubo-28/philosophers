/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:44:42 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/18 16:08:38 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_env *env, int i)
{
	long	now;
	long	tmp;
	t_time	time;

	tmp = 0;
	gettimeofday(&time, NULL);
	now = adj_time_form(&time);
	pthread_mutex_lock(&env->sts_mutexs[i]);
	if (env->philos[i].last_eat != NOTSET)
		tmp = now - env->philos[i].last_eat;
	pthread_mutex_unlock(&env->sts_mutexs[i]);
	if (tmp > env->time_to_die)
	{
		pthread_mutex_lock(&env->msg_mutex);
		printf("%ld %d died\n", now, env->philos[i].num);
		pthread_mutex_lock(&env->sts_mutexs[i]);
		env->philos[i].status = DEAD;
		pthread_mutex_unlock(&env->sts_mutexs[i]);
		set_fin_philos(env);
		pthread_mutex_unlock(&env->msg_mutex);
		return (FINISH);
	}
	return (0);
}

static int	check_count(t_env *env, int ach_num)
{
	if (ach_num == env->num_of_philos)
	{
		set_fin_philos(env);
		return (FINISH);
	}
	return (0);
}

static void	check_start(t_env *env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < env->num_of_philos)
	{
		pthread_mutex_lock(&env->sts_mutexs[i]);
		if (env->philos[i].status == START)
			count++;
		pthread_mutex_unlock(&env->sts_mutexs[i]);
		i++;
	}
	i = 0;
	while (count == env->num_of_philos && i < env->num_of_philos)
	{
		pthread_mutex_lock(&env->sts_mutexs[i]);
		env->philos[i].status = GO;
		pthread_mutex_unlock(&env->sts_mutexs[i]);
		i++;
	}

}

void	*monitor(void *arg)
{
	int		i;
	int		ach_num;
	t_env	*env;

	env = (t_env *)arg;
	while (1)
	{
		ach_num = 0;
		i = 0;
		while (i < env->num_of_philos)
		{
			check_start(env);
			if (check_death(env, i) == FINISH)
				return (NULL);
			if (env->must_eat_num != NOTSET)
			{
				pthread_mutex_lock(env->philos[i].sts_mutex);
				if (env->philos[i].eat_times >= env->must_eat_num)
					ach_num++;
				pthread_mutex_unlock(env->philos[i].sts_mutex);
			}
			i++;
		}
		if (check_count(env, ach_num) == FINISH)
			return (NULL);
	}
}
