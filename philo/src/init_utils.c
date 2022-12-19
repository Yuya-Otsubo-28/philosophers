/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:20:16 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/19 09:19:26 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	t_time	time;
	long	res;

	gettimeofday(&time, NULL);
	res = adj_time_form(&time);
	return (res);
}

// int	env_mutex_init(t_env *env)
// {
// 	pthread_mutex_t	*msg_mutex;

// 	msg_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
// 	if (!msg_mutex)
// 		return (MALLOC_ERROR);
// 	env->msg_mutex = msg_mutex;
// 	return (0);
// }
