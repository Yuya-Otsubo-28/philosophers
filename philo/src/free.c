/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:42:43 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/15 01:57:28 by yotsubo          ###   ########.fr       */
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

void	destroy_forks(t_fork **forks, int num_of_forks)
{
	int	i;

	i = 0;
	while (i < num_of_forks)
	{
		pthread_mutex_destroy(&forks[i]->fork);
		free(forks[i]);
		i++;
	}
	free(forks);
}

void	*free_env(t_env *env, int free_status)
{
	if (free_status == FORKS || free_status == ALL)
		// destroy_forks(env->forks, env->num_of_philos);
	if (free_status == PHILOS_AND_FROKS)
	{
		free_philos(env->philos, env->num_of_philos);
		destroy_forks(env->forks, env->num_of_philos);
	}
	if (free_status == PHILOS || free_status == ALL)
		free_philos(env->philos, env->num_of_philos);
	if (free_status == THREAD || free_status == ALL)
		free(env->th);
	pthread_mutex_destroy(env->env_mutex);
	free(env->env_mutex);
	pthread_mutex_destroy(env->msg_mutex);
	free(env->msg_mutex);
	free(env);
	return (NULL);
}