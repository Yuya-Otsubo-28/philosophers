/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:23:34 by yotsubo           #+#    #+#             */
/*   Updated: 2022/11/30 10:30:48 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long adj_time_form(t_time *time)
{
    long res;

    res = time->tvf_sec * 100;
    res += time->tv_usec / 100;
    return (res);
}