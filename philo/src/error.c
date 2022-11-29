#include "philo.h"
#include <unistd.h>

void error_handler(int enum)
{
    if (enum == ARGS_ERROR)
        ft_putstr_fd("*** ARGUMENT ERROR ***/n", STDERR_FILENO)
}