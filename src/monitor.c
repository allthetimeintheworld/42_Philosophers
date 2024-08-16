/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:04:52 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/16 18:04:25 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_check(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->dead)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

int	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock_mutex);
	if (get_timestamp() - philo->prev_meal >= philo->data->time_to_die \
	&& !philo->eating)
	{
		pthread_mutex_unlock(&philo->data->print_lock_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->print_lock_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (!death_check(data))
	{
		i = -1;
		while (++i < data->num_of_threads)
		{
			if (philo_died(&data->philo[i]))
			{
				print_status("died", &data->philo[i]);
				turn_dead(data);
			}
			thread_finished(data);
		}
		usleep(1000);
	}
	return (NULL);
}

void	turn_dead(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->dead = true;
	pthread_mutex_unlock(&data->death_mutex);
}

int	thread_finished(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_threads)
	{
		pthread_mutex_lock(&data->print_lock_mutex);
		if (!data->philo[i].finished)
		{
			pthread_mutex_unlock(&data->print_lock_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->print_lock_mutex);
		i++;
	}
	turn_dead(data);
	return (1);
}
