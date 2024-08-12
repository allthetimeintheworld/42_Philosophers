/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:17:49 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/12 14:52:48 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	if (!data || !av)
		return (1);
	data->philo_count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->philo_count <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (1);
	if (ac == 6)
		data->number_of_meals = ft_atoi(av[5]);
	else
		data->number_of_meals = -1;
	data->she_died = 0;
	data->philo_full = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);
	if (pthread_mutex_init(&data->death_lock, NULL) != 0
		|| pthread_mutex_init(&data->full, NULL) != 0)
	{
		free(data->forks);
		return (1);
	}
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&data->forks[j++]);
			pthread_mutex_destroy(&data->death_lock);
			pthread_mutex_destroy(&data->full);
			free(data->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philos(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->philo_count);
	if (!philo)
		err_msg("Error: Malloc failed\n");
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			err_msg("Error: Mutex init failed\n");
		}
		i++;
	}
	pthread_mutex_init(&data->write_lock, NULL);
	return (0);
}

int	start_sim(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->philo_count)
	{
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % data->philo_count;
		philo[i].eat_count = 0;
		philo[i].last_eat = get_time();
		philo[i].data = data;
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_routine, data);
	pthread_join(data->monitor, NULL);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}

