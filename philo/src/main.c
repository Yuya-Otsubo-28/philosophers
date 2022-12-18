/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:05:37 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/18 17:39:15 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init(int argc, char *argv[], t_env *env)
{
	int				func_return;
	t_time			time;

	func_return = init_env(argc, argv, env, &time);
	if (func_return)
	{
		error_handler(func_return);
		return (func_return);
	}
	init_philo_fork(env);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_env			env;
	int				event_res;

	if (!(argc == MUST_ARGS_NUM || argc == ADDED_ARGS_NUM))
		return (error_handler(ARGS_ERROR));
	if (init(argc, argv, &env))
		return (-1);
	event_res = event_start(&env);
	if (event_res == MALLOC_ERROR || event_res == PTHREAD_ERROR)
	{
		error_handler(event_res);
		return (-1);
	}
	return (0);
}
