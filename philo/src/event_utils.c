/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:26:38 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/19 13:38:04 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_start(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->sts_mutex);
		if (philo->status == GO)
		{
			pthread_mutex_unlock(philo->sts_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->sts_mutex);
	}
}
