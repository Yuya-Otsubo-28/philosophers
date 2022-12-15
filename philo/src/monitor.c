/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:44:42 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/15 09:00:39 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	int		i;
	int		ach_num;
	t_env	*env;
	long	now;
	t_time	time;
	long	tmp;

	env = (t_env *)arg;
	while (1)
	{
		ach_num = 0;
		i = 0;
		while (i < env->num_of_philos)
		{
			gettimeofday(&time, NULL);
			now = adj_time_form(&time);
			pthread_mutex_lock(env->philos[i]->sts_mutex);
			tmp = now - env->philos[i]->last_eat;
			pthread_mutex_unlock(env->philos[i]->sts_mutex);
			if (tmp > env->time_to_die)
			{
				pthread_mutex_lock(env->philos[i]->msg_mutex);
				printf("%ld %d died\n", now, env->philos[i]->num);
				pthread_mutex_lock(env->philos[i]->sts_mutex);
				env->philos[i]->status = DEAD;
				pthread_mutex_unlock(env->philos[i]->sts_mutex);
				set_fin_philos(env);
				pthread_mutex_unlock(env->philos[i]->msg_mutex);
				return (NULL);
			}
			if (env->must_eat_num != NOTSET)
			{
				pthread_mutex_lock(env->philos[i]->sts_mutex);
				if (env->philos[i]->eat_times >= env->must_eat_num)
					ach_num++;
				pthread_mutex_unlock(env->philos[i]->sts_mutex);
			}
			i++;
		}
		if (ach_num == env->num_of_philos)
		{
			lock_all_sts(env);
			set_fin_philos(env);
			unlock_all_sts(env);
			return (NULL);
		}
	}
}
