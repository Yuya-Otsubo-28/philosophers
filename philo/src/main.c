/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:05:37 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/01 17:57:49 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
    t_env env;
    t_philo **philos;
    t_time time;
    pthread_mutex_t msg_mutex;

    if (!(argc == MUST_ARGS_NUM || argc == ADDED_ARGS_NUM))
        return (error_handler(ARGS_ERROR));
    init_env(argc, argv, &env, &time);
    pthread_mutex_init(&msg_mutex, NULL);
    env.msg_mutex = &msg_mutex;
    philos = NULL;
    if (init_philo_fork(&env, philos) == -1)
        return (-1);
    puts("hi");
    event_start(philos, &env);
    //後片付け
}