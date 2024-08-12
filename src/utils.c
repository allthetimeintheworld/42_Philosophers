/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:22:35 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/12 14:51:17 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while ((s[i] == 32) || (s[i] >= 9 && s[i] <= 13))
		i++;
	while (is_digit(s[i]))
	{
		res = res * 10 + (s[i] - 48);
		i++;
	}
	return (res);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	if (gettimeofday(&tv, NULL) != 0)
	{
		err_msg("Error: gettimeofday failed\n");
		return (-1);
	}
	time = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (time);
}

int	ft_usleep(long time)
{
	long	start;
	long	current;

	start = get_time();
	if (start == -1)
		return (-1);
	while (1)
	{
		current = get_time();
		if (current == -1)
			return (-1);
		if (current - start >= time)
			break ;
		usleep(100);
	}
	return (0);
}

int	err_msg(char *err_msg)
{
	printf("Error: %s\n", err_msg);
	exit (1);
}


