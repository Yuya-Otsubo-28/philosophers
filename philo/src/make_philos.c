/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:11:01 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/17 22:48:16 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_one(void *arg)
{
	t_philo *philo;
	t_time	time;
	long	start;
	int		time_to_die;

	philo = (t_philo *)arg;
	time_to_die = philo->env->time_to_die;
	gettimeofday(&time, NULL);
	start = adj_time_form(&time);
	philo->last_eat = start;
	printf("%ld %d is thinking\n", start, philo->num);
	printf("%ld %d is taking a fork\n", start, philo->num);
	printf("%ld %d died\n", start + time_to_die, philo->num);
	return (NULL);
}

static int	philo_one_case(t_env *env)
{
	if (pthread_create(&env->th[0], NULL, &philo_one, env->philos[0]))
		return (PTHREAD_ERROR);
	if (pthread_detach(env->th[0]))
		return (PTHREAD_ERROR);
	return (0);
}

int	event_start(t_env *env)
{
	int	i;

	env->th = (pthread_t *)malloc(sizeof(pthread_t) * (env->num_of_philos + 2));
	if (!env->th)
		return (MALLOC_ERROR);
	if (env->num_of_philos == 1)
	{
		if (philo_one_case(env))
			return (PTHREAD_ERROR);
		return (0);
	}
	printf("%d : %p\n", 0, env->philos[0]->env);
	printf("%d : %p\n", 1, env->philos[1]->env);
	i = 0;
	while (i < env->num_of_philos)
	{
		printf("%d\n", i);
		if (pthread_create(&env->th[i], NULL, &philo_event, env->philos[i]))
			return (PTHREAD_ERROR);
		if (pthread_detach(env->th[i]))
			return (PTHREAD_ERROR);
		i++;
	}
	if (env->num_of_philos == 1)
	{
		if (philo_one_case(env))
			return (PTHREAD_ERROR);
		return (0);
	}
	if (pthread_create(&env->th[i], NULL, &monitor, env) != 0)
		return (PTHREAD_ERROR);
	if (pthread_join(env->th[i], NULL) != 3)
		return (PTHREAD_ERROR);
	return (0);
}
