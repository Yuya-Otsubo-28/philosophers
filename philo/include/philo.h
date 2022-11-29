#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>

#define MUST_ARGS_NUM 5
#define ADDED_ARGS_NUM 6
#define ARGS_ERROR 0
#define MALLOC_ERROR 1

typedef struct s_env t_env;
typedef struct s_fork t_fork;
typedef struct s_philo t_philo;
typedef struct timeval t_time;

struct s_env {
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    int num_of_philos;
    int must_eat_num;
    t_time *start_time;
};

struct s_fork {
    pthread_mutex_t *fork;
};

struct s_philo {
    t_env *env;
    t_fork *right;
    t_fork *left;
    int last_eat;
    int last_sleep;
    int num;
};

void init_philo_fork(t_env *env, t_philo *philo);

void init_env(int argc, char *argv[], t_env *env);

void error_handler(int error_num);

void destroy_forks(t_fork *fork, int num_of_forks);

#endif