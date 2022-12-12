/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:11:01 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/12 16:16:08 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
* thのallocate失敗のチェックをしっかり入れておく
*/
void	event_start(t_philo **philos, t_env *env)
{
	int	i;

	env->th = (pthread_t *)malloc(sizeof(pthread_t) * env->num_of_philos);
	i = -1;
	while (++i < env->num_of_philos)
		pthread_create(&env->th[i], NULL, &philo_event, philos[i]);
	pthread_create(&env->th[i], NULL, &monitor, env);
	pthread_join(env->th[i], NULL);
}
