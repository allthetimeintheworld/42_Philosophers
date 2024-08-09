/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:38:37 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/08 15:56:16 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
