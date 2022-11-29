#incude "philo.h"

void init_env(int argc, char *argv[], t_env *env)
{
    env->num_of_philos = ph_atoi(argv[1]);
    env->time_to_die = ph_atoi(argv[2]);
    env->time_to_eat = ph_atoi(argv[3]);
    env->time_to_sleep = ph_atoi(argv[4]);
    if (argc == ADDED_ARGS_NUM)
        env->must_eat_nums = ph_atoi(argv[5]);
}

t_fork *init_forks(t_env *env)
{
    t_fork *forks;
    size_t i;

    forks = (t_fork *)malloc(sizeof(t_fork) * env->num_of_philos);
    if (!forks)
        return (NULL);
    i = -1;
    while (++i < env->num_of_philos)
        pthread_mutex_init(forks[i]->fork, NULL);
    return (forks);
}

t_philo *init_philo_fork(t_env *env, t_philo *philo)
{
    t_fork *forks;
    t_philo *philos;

    forks = init_forks(env);
    if (!forks)
        return (NULL);
    philos = (t_philo *)malloc(sizeof(t_philo) * env->num_of_philos);
    if (!philo)
        return (NULL);
}