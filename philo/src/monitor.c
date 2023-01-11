/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:44:42 by yotsubo           #+#    #+#             */
/*   Updated: 2023/01/11 11:25:10 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_env *env, int i)
{
	long	now;
	long	tmp;

	tmp = 0;
	now = get_time();
	pthread_mutex_lock(&env->sts_mutexs[i]);
	if (env->philos[i].last_eat != NOTSET)
		tmp = now - env->philos[i].last_eat;
	pthread_mutex_unlock(&env->sts_mutexs[i]);
	if (tmp > env->time_to_die)
	{
		pthread_mutex_lock(&env->msg_mutex);
		lock_all_sts(env);
		printf("\x1b[31m%ld %d died\n\x1b[0m", now, env->philos[i].num);
		env->fin = FINISH;
		unlock_all_sts(env);
		pthread_mutex_unlock(&env->msg_mutex);
		return (FINISH);
	}
	return (0);
}

static int	check_count(t_env *env, int ach_num)
{
	if (ach_num == env->num_of_philos)
	{
		set_fin_philos(env, NOTSET);
		return (FINISH);
	}
	return (0);
}

static void	check_start(t_env *env, int *flag)
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
		*flag = 1;
		i++;
	}
}

void	*monitor(void *arg)
{
	int			i;
	static int	flag;
	int			ach_num;
	t_env		*env;

	env = (t_env *)arg;
	while (1)
	{
		ach_num = 0;
		i = 0;
		while (i < env->num_of_philos)
		{
			if (!flag)
				check_start(env, &flag);
			if (check_death(env, i) == FINISH)
				return (NULL);
			if (env->must_eat_num != NOTSET)
				ach_num = inc_ach(env, ach_num, i);
			i++;
		}
		if (check_count(env, ach_num) == FINISH)
			return (NULL);
	}
}
