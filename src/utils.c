/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:22:35 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/09 12:49:57 by jadyar           ###   ########.fr       */
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

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (time);
}

int	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		ft_usleep(100);
	}
	return (0);
}

int	err_msg(char *err_msg)
{
	printf("Error: %s\n", err_msg);
	return (1);
}

/* int	check_input(int argc, char **argv)
{
	if (argc < 5)
		return (WRONG_INPUT);
	if (argc > 6)
		return (WRONG_INPUT);
	if (is_input_digit(argc, argv) != 0)
		return (WRONG_INPUT);
	if (wrong_input_check(argc, argv))
		return (WRONG_INPUT);
	return (0);
} */
