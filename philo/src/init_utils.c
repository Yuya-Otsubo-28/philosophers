/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:20:16 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/19 13:37:45 by yotsubo          ###   ########.fr       */
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

void	mod_usleep(int sleep_time)
{
	long	end;

	end = get_time() + sleep_time;
	while (get_time() <= end)
		;
}

int	init_sts(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		if (pthread_mutex_init(&env->sts_mutexs[i], NULL))
			return (PTHREAD_ERROR);
		i++;
	}
	return (0);
}
