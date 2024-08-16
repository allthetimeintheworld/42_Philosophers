/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:04:01 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/16 14:14:34 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int ac, char **av)
{
	int	i; 

	i = 1;
	while (i < ac)
	{
		if (!is_num(av[i]) || ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	if (ac == 6)
	{
		if (ft_atoi(av[5]) < 1)
			return (0);
	}
	return (1);
}

int	is_num(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!ft_is_digit(av[i]))
			return (0);
		i++;
	}
	return (1);
}
