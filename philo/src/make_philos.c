/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:11:01 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/19 13:33:07 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_one(void *arg)
{
	t_philo	*philo;
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
	if (pthread_create(&env->th[0], NULL, &philo_one, &env->philos[0]))
		return (PTHREAD_ERROR);
	if (pthread_join(env->th[0], NULL))
		return (PTHREAD_ERROR);
	return (0);
}

int	event_start(t_env *env)
{
	int	i;

	if (env->num_of_philos == 1)
	{
		if (philo_one_case(env))
			return (PTHREAD_ERROR);
		return (0);
	}
	i = 0;
	while (i < env->num_of_philos)
	{
		if (pthread_create(&env->th[i], NULL, &philo_event, &env->philos[i]))
			return (PTHREAD_ERROR);
		i++;
	}
	while (i-- > 0)
	{
		if (pthread_detach(env->th[i]))
			return (PTHREAD_ERROR);
	}
	if (pthread_create(&env->th[env->num_of_philos], NULL, &monitor, env))
		return (PTHREAD_ERROR);
	if (pthread_join(env->th[env->num_of_philos], NULL))
		return (PTHREAD_ERROR);
	return (0);
}
