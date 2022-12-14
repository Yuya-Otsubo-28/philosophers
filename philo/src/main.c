/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:05:37 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/14 15:58:59 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int				func_return;
	t_env			*env;
	t_philo			**philos;
	t_time			time;
	pthread_mutex_t	msg_mutex;

	if (!(argc == MUST_ARGS_NUM || argc == ADDED_ARGS_NUM))
		return (error_handler(ARGS_ERROR));
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (error_handler(MALLOC_ERROR));
	func_return = init_env(argc, argv, env, &time);
	if (func_return)
		return (error_handler(func_return));
	pthread_mutex_init(&msg_mutex, NULL);
	env->msg_mutex = &msg_mutex;
	philos = NULL;
	philos = init_philo_fork(env, philos);
	if (!philos)
		return (-1);
	event_start(philos, env);
	return (0);
}
/*最後後片付けもしっかり*/
