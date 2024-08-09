/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:13:02 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/09 13:00:40 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		if (i < data->philo_count)
		{
			pthread_mutex_lock(&data->death_lock);
			if (get_time() - data->philos[i].last_eat > data->time_to_die)
			{
				print_status(&data->philos[i], "died");
				data->she_died = 1;
				pthread_mutex_unlock(&data->death_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->death_lock);
			i++;
		}
		//i = 0;
		ft_usleep(1000);
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	data->start_time = get_time();
	while (i < data->philo_count)
	{
		data->philos[i].last_eat = data->start_time;
		pthread_create(&data->philos[i].thread, NULL, philo_routine, \
			&data->philos[i]);
	}
	pthread_create(&monitor_thread, NULL, monitor_routine, data);
	while (i < data->philo_count)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->death_lock);
		if (data->she_died)
		{
			pthread_mutex_unlock(&data->death_lock);
			break ;
		}
		{
			pthread_mutex_unlock(&data->death_lock);
			pthread_mutex_lock(&data->forks[philo->id]);
			print_status(philo, TAKE_FORKS);
			pthread_mutex_lock(&data->forks[(philo->id + 1) \
				% data->philo_count]);
			print_status(philo, TAKE_FORKS);
			print_status(philo, EAT);
			philo->last_eat = get_time();
			ft_usleep(data->time_to_eat);
			philo->eat_count++;
			pthread_mutex_unlock(&data->forks[philo->id]);
			pthread_mutex_unlock(&data->forks[(philo->id + 1) \
				% data->philo_count]);
			print_status(philo, SLEEP);
			ft_usleep(data->time_to_sleep);
			print_status(philo, THINK);
			if (data->number_of_meals != -1 && \
				philo->eat_count >= data->number_of_meals)
			{
				pthread_mutex_lock(&data->full);
				data->philo_full++;
				pthread_mutex_unlock(&data->full);
				break ;
			}
		}
	}
	return (NULL);
}
