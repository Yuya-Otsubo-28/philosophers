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

#define SLEEP 0
#define EAT 1
#define TAKE 2
#define THINK 3
#define DEAD 4

#define RIGHT 1
#define LEFT 2

#define FINISH 1
#define NOTFIN -1

#define NOTSET -1

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
    t_philo *philos;
    t_fork **forks;
};

struct s_fork {
    pthread_mutex_t *fork;
};

struct s_philo {
    t_env *env;
    t_fork *right;
    t_fork *left;
    t_time *lsat_eat;
    t_time *last_sleep;
    pthread_mutex_t *msg_mutex;
    pthread_mutex_t *sts_mutex
    int status;
    int num;
    int eat_times;
};

void init_philo_fork(t_env *env, t_philo *philo);

void init_env(int argc, char *argv[], t_env *env, t_time *time);

int error_handler(int error_num);

void destroy_forks(t_fork **forks, int num_of_forks);

void	ft_putstr_fd(char *s, int fd);

int ph_atoi(const char *str);

size_t	ft_strlen(const char *str);

long adj_time_form(t_time *time);

#endif