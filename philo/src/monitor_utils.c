/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:41:53 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/15 03:10:06 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*set_fin_philos(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		env->philos[i]->status = FINISH;
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
		pthread_mutex_unlock(env->philos[i]->sts_mutex);
		i++;
	}
}

void	lock_all_sts(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_mutex_lock(env->philos[i]->sts_mutex);
		i++;
	}
}
