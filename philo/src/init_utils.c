/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:20:16 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/15 10:49:42 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_member(t_env *env, t_philo **philos,
	t_fork **forks, pthread_mutex_t *sts_mutex)
{
	int				i;

	i = 0;
	while (i < env->num_of_philos)
		pthread_mutex_init(&sts_mutex[i++], NULL);
	while (i-- > 0)
	{
		if (i == 0 && env->num_of_philos > 1)
			philos[0]->left = forks[env->num_of_philos - 1];
		else
			philos[i]->left = forks[i - 1];
		philos[i]->right = forks[i];
		philos[i]->sts_mutex = &sts_mutex[i];
		philos[i]->env = env;
		philos[i]->num = i + 1;
		philos[i]->msg_mutex = env->msg_mutex;
		philos[i]->last_eat = env->start_time;
		philos[i]->eat_times = 0;
	}
	return (0);
}

int	env_mutex_init(t_env *env)
{
	pthread_mutex_t	*msg_mutex;

	msg_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!msg_mutex)
		return (MALLOC_ERROR);
	env->msg_mutex = msg_mutex;
	return (0);
}
