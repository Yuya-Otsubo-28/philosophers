#include "philo.h"

int main(int argc, char *argv[])
{
    t_env env;
    t_philo *philos;
    t_time time;

    if (!(argc == MUST_ARGS_NUM || argc == ADDED_ARGS_NUM))
        error_handler(ARGS_ERROR);
    gettimeofday(&time, NULL);
    env.start_time = &time;
    init_env(argc, argv, &env);
    philos = NULL;
    init_philo_fork(&env, philos);
}