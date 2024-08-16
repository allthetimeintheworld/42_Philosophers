/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:04:56 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/16 17:02:37 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	is_sleeping(t_philo *philo)
{
	print_status("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	is_thinking(t_philo *philo)
{
	size_t	time;

	print_status("is thinking", philo);
	time = philo->data->time_to_die - philo->data->time_to_eat
		- philo->data->time_to_sleep;
	if (!death_check(philo->data))
	{
		if ((philo->data->num_of_threads % 2) == 0)
			usleep(10);
		else
		{
			if (time <= 0)
				usleep(900);
			else
				usleep(time * 900);
		}
	}
}

int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	print_status("has taken a fork", philo);
	if (philo->data->num_of_threads == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	print_status("has taken a fork", philo);
	return (1);
}

void	is_eating(t_philo *philo)
{
	if (!death_check(philo->data) && take_fork(philo))
	{
		print_status("is eating", philo);
		pthread_mutex_lock(&philo->data->print_lock_mutex);
		philo->prev_meal = get_timestamp();
		philo->meal_count += 1;
		philo->eating = true;
		pthread_mutex_unlock(&philo->data->print_lock_mutex);
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_lock(&philo->data->print_lock_mutex);
		philo->eating = false;
		if (philo->data->meals_required != -1
			&& philo->meal_count >= philo->data->meals_required)
			philo->finished = true;
		pthread_mutex_unlock(&philo->data->print_lock_mutex);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(&(philo->data->death_mutex));
	philo->prev_meal = get_timestamp();
	pthread_mutex_unlock(&(philo->data->death_mutex));
	if (philo->id % 2 == 0)
		ft_usleep(1000);
	while (!death_check(data))
	{
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (arg);
}

/* void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->data->death_mutex));
	philo->prev_meal = get_timestamp();
	pthread_mutex_unlock(&(philo->data->death_mutex));
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (1)
	{
		take_fork(philo);
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
} */
