/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:05:17 by yotsubo           #+#    #+#             */
/*   Updated: 2022/11/30 17:12:50 by yotsubo          ###   ########.fr       */
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
    env->start_time = adj_time_form(time);
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

static int init_member(t_env *env, t_philo **philos, t_fork **forks)
{
    int i;
    pthread_mutex_t *sts_mutex;

    sts_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * env->num_of_philos);
    if (!sts_mutex)
        return (MALLOC_ERROR);
    i = 0;
    while (i < env->num_of_philos)
        pthread_mutex_init(&sts_mutex[i++], NULL);
    while (i-- > 0)
    {
        if (i == 0)
            philos[0]->left = forks[env->num_of_philos - 1];
        else
            philos[i]->left = forks[i - 1];
        philos[i]->right = forks[i];
        philos[i]->sts_mutex = &sts_mutex[i];
        philos[i]->env = env;
        philos[i]->num = i + 1;
        philos[i]->msg_mutex = env->msg_mutex;
        philos[i]->last_eat = env->start_time;
        philos[i]->eat_times = 0;
    }
    return (0);
}

static t_philo **allc_philos(t_env *env)
{
    int i;
    t_philo **philos;

    philos = (t_philo **)malloc(sizeof(t_philo *) * env->num_of_philos);
    if (!philos)
        return (NULL);
    i = 0;
    while (i < env->num_of_philos)
    {
        philos[i] = (t_philo *)malloc(sizeof(t_philo));
        if (!philos[i])
        {
            while (i-- > 0)
                free(philos[i]);
            free(philos);
            return (NULL);
        }
        i++;
    }
    return (philos);
}

static t_philo **init_philos(t_env *env, t_fork **forks)
{
    t_philo **philos;
    pthread_mutex_t *sts_mutex;

    philos = allc_philos(env);
    if (!philos)
        return (NULL);
    sts_mutex =  (pthread_mutex_t *)malloc(sizeof(pthread_t) * env->num_of_philos);
    if (!sts_mutex)
    {
        free_philos(philos, env->num_of_philos);
        return (NULL);
    }
    if (init_member(env, philos, forks) == MALLOC_ERROR)
    {
        destroy_sts(sts_mutex, env->num_of_philos);
        free_philos(philos, env->num_of_philos);
        return (NULL);
    }
    return (philos);
}

void init_philo_fork(t_env *env, t_philo **philos)
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