#include "philo.h"

int main(int argc, char *argv[])
{
    t_env env;
    t_philo *philos

    if (!(argc == MUST_ARGS_NUM || argc == ADDED_ARGS_NUM))
        error_handler(ARGS_ERROR);
    init_env(argc, argv, &env);
    init_philo_fork()
}