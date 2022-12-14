/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:05:50 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/14 22:41:10 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handler(int error_num)
{
	if (error_num == ARGS_ERROR)
		ft_putstr_fd("*** ARGUMENT ERROR ***\n", STDERR_FILENO);
	if (error_num == MALLOC_ERROR)
		ft_putstr_fd("*** MALLOC ERROR ***\n", STDERR_FILENO);
	if (error_num == TIME_ERROR)
		ft_putstr_fd("*** GETTIMEOFDAY ERROR ***\n", STDERR_FILENO);
	if (error_num == PTHREAD_ERROR)
		ft_putstr_fd("*** PTHREAD ERROR ***\n", STDERR_FILENO);
	return (-1);
}
