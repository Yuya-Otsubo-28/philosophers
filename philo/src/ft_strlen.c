/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo </var/mail/yotsubo>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:14:37 by yotsubo           #+#    #+#             */
/*   Updated: 2022/06/07 19:33:44 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
/*
int	main(void)
{
	char	s[] = "1234567890";
	
	printf("string : %s\n", s);
	printf("result : %ld\n", ft_strlen(s));
	return (0);
}
*/
