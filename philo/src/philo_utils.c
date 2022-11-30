/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:23:34 by yotsubo           #+#    #+#             */
/*   Updated: 2022/11/30 16:31:24 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long adj_time_form(t_time *time)
{
    long res;

    res = time->tv_sec * 100;
    res += time->tv_usec / 100;
    return (res);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while ((size_t)INT_MAX < len)
	{
		write(fd, s, INT_MAX);
		len -= INT_MAX;
		s += INT_MAX;
	}
	write(fd, s, len);
}

size_t	ft_strlen(const char *str)
{
	size_t	size;
	char	*s;

	s = (char *)str;
	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

static long	ft_atol(const char *str)
{
	long	res;
	int		flag;
	size_t	i;

	flag = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			flag *= -1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (res * flag);
}

int ph_atoi(const char *str)
{
	long tmp;

	tmp = ft_atol(str);
	if (tmp < 0 || tmp > INT_MAX)
		error_handler(ARGS_ERROR);
	return ((int)tmp);
}