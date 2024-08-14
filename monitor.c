/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:55:02 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/14 17:51:14 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death(t_philosopher *philo)
{
	long	time_diff;

	if (!philo || !philo->data)
		return (1);
	pthread_mutex_lock(&philo->data->death_lock);
	time_diff = get_timestamp() - philo->last_meal;
	if (time_diff > philo->data->time_to_die)
	{
		print_status(philo, "died");
		philo->data->simulation_running = 0;
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	return (!philo->data->simulation_running);
}

void	*monitor_philosophers(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (data->simulation_running)
	{
		i = 0;
		while (i < data->num_philosophers)
		{
			 printf("Checking philosopher %d: philo pointer = %p\n", i, (void*)&data->philosophers[i]);
			if (check_death(&data->philosophers[i]))
				return (NULL);
			i++;
		}
		//usleep(1000);
	}
	return (NULL);
}
