/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:42:43 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/15 10:37:14 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philo **philos, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
		free(philos[i++]);
	free(philos);
}

void	destroy_sts(pthread_mutex_t *sts_mutex, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
		pthread_mutex_destroy(&sts_mutex[i++]);
	free(sts_mutex);
}

void	destroy_forks(t_env *env, int num_of_forks)
{
	int	i;

	i = 0;
	while (i < num_of_forks)
	{
		pthread_mutex_destroy(&env->forks[i]->fork);
		free(env->forks[i]);
		i++;
	}
	free(env->forks);
}

void	*free_env(t_env *env, int free_status)
{
	if (free_status == PHILOS_AND_FROKS || free_status == ALL)
	{
		free_philos(env->philos, env->num_of_philos);
		destroy_forks(env, env->num_of_philos);
	}
	if (free_status == ALL)
		free(env->th);
	pthread_mutex_destroy(env->msg_mutex);
	free(env->msg_mutex);
	destroy_sts(env->sts_mutexs, env->num_of_philos);
	free(env);
	return (NULL);
}
