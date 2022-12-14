/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:50:23 by yotsubo           #+#    #+#             */
/*   Updated: 2022/12/14 15:54:12 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <errno.h>

# define MUST_ARGS_NUM 5
# define ADDED_ARGS_NUM 6

# define ARGS_ERROR 1
# define MALLOC_ERROR 2

# define SLEEP 1
# define EAT 2
# define TAKE 3
# define THINK 5
# define DEAD 4
# define FINISH 6

# define RIGHT 1
# define LEFT -1

# define NOTFIN 0

# define NOTSET -1

typedef struct s_env	t_env;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct timeval	t_time;

struct s_env {
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				num_of_philos;
	int				must_eat_num;
	long			start_time;
	t_philo			**philos;
	t_fork			**forks;
	pthread_t		*th;
	pthread_mutex_t	*msg_mutex;
	pthread_mutex_t	*env_mutex;
};

struct s_fork {
	pthread_mutex_t	fork;
};

struct s_philo {
	t_env			*env;
	t_fork			*right;
	t_fork			*left;
	long			last_eat;
	pthread_mutex_t	*msg_mutex;
	pthread_mutex_t	*sts_mutex;
	int				status;
	int				num;
	int				eat_times;
};

/* * * * * * * * * */
/*     init.c      */
/* * * * * * * * * */

t_philo	**init_philo_fork(t_env *env, t_philo **philos);

int		init_env(int argc, char *argv[], t_env *env, t_time *time);

/* * * * * * * * * */
/*  philo_utils.c  */
/* * * * * * * * * */

long	adj_time_form(t_time *time);

void	ft_putstr_fd(char *s, int fd);

size_t	ft_strlen(const char *str);

int		ph_atoi(const char *str);

/* * * * * * * * * */
/*    error.c      */
/* * * * * * * * * */

int		error_handler(int error_num);

void	free_philos(t_philo **philos, int num_of_philos);

void	destroy_sts(pthread_mutex_t *sts_mutex, int num_of_philos);

void	destroy_forks(t_fork **forks, int num_of_forks);

/* * * * * * * * * */
/*  make_philos.c  */
/* * * * * * * * * */

void	event_start(t_philo **philos, t_env *env);

/* * * * * * * * * */
/*  philo_event.c  */
/* * * * * * * * * */

void	*philo_event(void *arg);

/* * * * * * * * * */
/* judge_finish.c  */
/* * * * * * * * * */

void	*monitor(void *arg);

/* * * * * * * * * */
/* judge_finish.c  */
/* * * * * * * * * */

int		dis_msg(t_philo *philo, int status);
#endif
