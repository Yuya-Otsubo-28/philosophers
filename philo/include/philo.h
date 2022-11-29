#ifndef PHILO_H
# define PHILO_H

#define MUST_ARGS_NUM 5
#define ADDED_ARGS_NUM 6
#define ARG_ERROR 0
#define MALLOC_ERROR 1

typedef s_env t_env;
typedef s_fork t_fork;
typedef s_philo t_philo;

struct s_env {
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    int num_of_philos;
    int must_eat_num;
};

struct s_fork {
    pthread_mutex_t *fork;
};

struct s_philo {
    t_env *env;
    t_fork *right;
    t_fork *left;
    int num;
}

#endif