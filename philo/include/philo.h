/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:50:23 by yotsubo           #+#    #+#             */
/*   Updated: 2023/02/18 11:36:35 by yotsubo          ###   ########.fr       */
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

# define MAX_NUM 201
# define MUST_ARGS_NUM 5
# define ADDED_ARGS_NUM 6

# define ARGS_ERROR 1
# define MALLOC_ERROR 2
# define TIME_ERROR 3
# define PTHREAD_ERROR 4

# define SLEEP 1
# define EAT 2
# define TAKE 3
# define THINK 5
# define DEAD 4
# define FINISH 6

# define RIGHT 1
# define LEFT -1

# define ALL 1
# define ONLY_INFO 2
# define PHILOS_AND_FROKS 4
# define PHILOS 5

# define NOTFIN 0

# define NOTSET -1
# define START 1
# define GO 7

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;
typedef struct timeval	t_time;

struct s_philo {
	t_info			*info;
	int				right;
	int				left;
	long			last_eat;
	long			last_action;
	pthread_mutex_t	*msg_mutex;
	pthread_mutex_t	*sts_mutex;
	int				status;
	int				num;
	int				eat_times;
};

struct s_info {
	long			start_time;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				num_of_philos;
	int				next_philo_num;
	int				must_eat_num;
	int				fin;
	t_philo			philos[MAX_NUM];
	pthread_mutex_t	forks[MAX_NUM];
	pthread_t		th[MAX_NUM];
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	num_mutex;
	pthread_mutex_t	sts_mutexs[MAX_NUM];
};

/* * * * * * * * * */
/*     init.c      */
/* * * * * * * * * */

int		init_philo_fork(t_info *info);

int		init_info(int argc, char *argv[], t_info *info, t_time *time);

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

void	destroy_forks(t_info *info, int num_of_forks);

void	*free_info(t_info *info, int free_status);

/* * * * * * * * * */
/*  make_philos.c  */
/* * * * * * * * * */

int		event_start(t_info *info);

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

int		dis_msg(t_philo *philo, int status, long sleep_time);

/* * * * * * * * * */
/* judge_finish.c  */
/* * * * * * * * * */

void	*set_fin_philos(t_info *info, int dead_philo);

void	unlock_all_sts(t_info *info);

void	lock_all_sts(t_info *info);

int		info_mutex_init(t_info *info);

long	get_time(void);

void	mod_usleep(int sleep_time);

void	wait_start(t_philo *philo);

int		inc_ach(t_info *info, int ach_num, int i);

int		init_sts(t_info *info);

#endif
