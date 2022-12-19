/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:05:17 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/19 13:37:41 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_env(int argc, char *argv[], t_env *env, t_time *time)
{
	env->num_of_philos = ph_atoi(argv[1]);
	env->time_to_die = ph_atoi(argv[2]);
	env->time_to_eat = ph_atoi(argv[3]);
	env->time_to_sleep = ph_atoi(argv[4]);
	if (env->num_of_philos == NOTSET || env->time_to_die == NOTSET
		|| env->time_to_eat == NOTSET || env->time_to_sleep == NOTSET)
		return (ARGS_ERROR);
	if (gettimeofday(time, NULL) == -1)
		return (TIME_ERROR);
	if (argc == ADDED_ARGS_NUM)
	{
		env->must_eat_num = ph_atoi(argv[5]);
		if (env->must_eat_num == NOTSET)
			return (ARGS_ERROR);
	}
	else
		env->must_eat_num = NOTSET;
	env->fin = NOTSET;
	if (init_sts(env))
		return (PTHREAD_ERROR);
	return (0);
}

static int	init_forks(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		if (pthread_mutex_init(&env->forks[i].fork, NULL))
			return (PTHREAD_ERROR);
		i++;
	}
	return (0);
}

static int	init_member(int i, t_philo *philo, t_env *env)
{
	philo->env = env;
	if (i == 0 && env->num_of_philos > 1)
		philo->left = &env->forks[env->num_of_philos - 1];
	else if (i == 0 && env->num_of_philos == 1)
		philo->left = &env->forks[0];
	else
		philo->left = &env->forks[i - 1];
	philo->right = &env->forks[i];
	philo->msg_mutex = &env->msg_mutex;
	philo->sts_mutex = &env->sts_mutexs[i];
	philo->status = NOTSET;
	philo->num = i + 1;
	philo->last_eat = NOTSET;
	philo->last_action = 0;
	philo->eat_times = 0;
	return (0);
}

static int	init_philos(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		init_member(i, &env->philos[i], env);
		i++;
	}
	return (0);
}

int	init_philo_fork(t_env *env)
{
	if (init_forks(env))
	{
		error_handler(PTHREAD_ERROR);
		return (PTHREAD_ERROR);
	}
	init_philos(env);
	return (0);
}
