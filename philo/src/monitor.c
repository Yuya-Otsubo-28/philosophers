/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:44:42 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/15 02:11:23 by yotsubo          ###   ########.fr       */
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

	env = (t_env *)arg;
	while (1)
	{
		ach_num = 0;
		i = 0;
		while (i < env->num_of_philos)
		{
			lock_all_sts(env);
			gettimeofday(&time, NULL);
			now = adj_time_form(&time);
			if (now - env->philos[i]->last_eat > env->time_to_die)
			{
				pthread_mutex_lock(env->philos[i]->msg_mutex);
				printf("%ld %d died\n", now, env->philos[i]->num);
				pthread_mutex_unlock(env->philos[i]->msg_mutex);
				env->philos[i]->status = DEAD;
				set_fin_philos(env);
				unlock_all_sts(env);
				return (NULL);
			}
			if (env->must_eat_num != NOTSET)
			{
				if (env->philos[i]->eat_times >= env->must_eat_num)
					ach_num++;
			}
			unlock_all_sts(env);
			i++;
		}
		if (ach_num == env->num_of_philos)
			return (set_fin_philos(env));
	}
}
