/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:05:17 by yotsubo           #+#    #+#             */
/*   Updated: 2022/11/30 12:52:48 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_env(int argc, char *argv[], t_env *env, t_time *time)
{
    env->num_of_philos = ph_atoi(argv[1]);
    env->time_to_die = ph_atoi(argv[2]);
    env->time_to_eat = ph_atoi(argv[3]);
    env->time_to_sleep = ph_atoi(argv[4]);
    gettimeofday(time, NULL);
    env->start_time = time;
    if (argc == ADDED_ARGS_NUM)
        env->must_eat_num = ph_atoi(argv[5]);
    else
        env->must_eat_num = NOTSET;
}

static t_fork **init_forks(t_env *env)
{
    t_fork **forks;
    int i;
    int j;

    forks = (t_fork **)malloc(sizeof(t_fork *) * env->num_of_philos);
    if (!forks)
        return (NULL);
    i = 0;
    while (i < env->num_of_philos)
    {
        forks[i] = (t_fork *)malloc(sizeof(t_fork));
        if (!forks)
        {
            while (i-- > 0)
                free(forks[i]);
            break ;
        }
    }
    j = 0;
    while (j < env->num_of_philos)
    {
        pthread_mutex_init(forks[j]->fork, NULL);
        j++;
    }
    return (forks);
}

static t_philo *init_philos(t_env *env, t_fork **forks)
{
    t_philo *philos;
    pthread_mutex_t msg;
    int i;

    philos = (t_philo *)malloc(sizeof(t_philo) * env->num_of_philos);
    if (!philos)
        return (NULL);
    pthread_mutex_init(&msg, NULL);
    i = 0;
    while (i < env->num_of_philos)
    {
        if (i == 0)
        {
            philos[0].right = forks[0];
            philos[0].left = forks[env->num_of_philos - 1];
        }
        else
        {
            philos[i].right = forks[i];
            philos[i].left = forks[i - 1];
        }
        philos[i].env = env;
        philos[i].num = i + 1;
        philos[i].msg = msg;
        philos[i].eat_times = 0;
        i++;
    }
    return (philos);
}

void init_philo_fork(t_env *env, t_philo *philos)
{
    t_fork **forks;

    forks = init_forks(env);
    if (!forks)
        error_handler(MALLOC_ERROR);
    philos = init_philos(env, forks);
    if (!philos)
    {
        destroy_forks(forks, env->num_of_philos);
        error_handler(MALLOC_ERROR);
    }
    env->philos = philos;
}