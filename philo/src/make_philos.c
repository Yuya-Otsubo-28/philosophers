/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:11:01 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/15 09:23:27 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	event_start(t_philo **philos, t_env *env)
{
	int	i;

	env->th = (pthread_t *)malloc(sizeof(pthread_t) * (env->num_of_philos + 1));
	if (!env->th)
		return (MALLOC_ERROR);
	i = -1;
	while (++i < env->num_of_philos)
	{
		if (pthread_create(&env->th[i], NULL, &philo_event, philos[i]))
		{
			error_handler(PTHREAD_ERROR);
			return (PTHREAD_ERROR);
		}
		if (pthread_detach(env->th[i]))
		{
			error_handler(PTHREAD_ERROR);
			return (PTHREAD_ERROR);
		}
	}
	if (pthread_create(&env->th[i], NULL, &monitor, env))
		return (PTHREAD_ERROR);
	if (pthread_join(env->th[i], NULL))
		return (PTHREAD_ERROR);
	return (0);
}
