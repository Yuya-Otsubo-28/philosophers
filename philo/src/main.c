/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:05:37 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/17 16:42:34 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_env	*init(int argc, char *argv[])
{
	int				func_return;
	t_time			time;
	t_env			*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
	{
		error_handler(MALLOC_ERROR);
		return (NULL);
	}
	func_return = init_env(argc, argv, env, &time);
	if (func_return)
	{
		free(env);
		error_handler(func_return);
		return (NULL);
	}
	env->philos = init_philo_fork(env, env->philos);
	if (!env->philos)
		return (free_env(env, ONLY_ENV));
	return (env);
}

int	main(int argc, char *argv[])
{
	t_env			*env;
	int				event_res;

	if (!(argc == MUST_ARGS_NUM || argc == ADDED_ARGS_NUM))
		return (error_handler(ARGS_ERROR));
	env = init(argc, argv);
	if (!env)
		return (-1);
	event_res = event_start(env->philos, env);
	if (event_res == MALLOC_ERROR || event_res == PTHREAD_ERROR)
	{
		if (event_res == MALLOC_ERROR)
			free_env(env, PHILOS_AND_FROKS);
		if (event_res == PTHREAD_ERROR)
			free_env(env, ALL);
		error_handler(event_res);
		return (-1);
	}
	//free_env(env, ALL);
	return (0);
}
