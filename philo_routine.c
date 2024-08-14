/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:37:37 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/14 17:14:13 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philosopher *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	if (first_fork == second_fork)
	{
		printf("Error: Double fork assigned to %d", philo->id);
		exit(1);
	}
	pthread_mutex_lock(first_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_status(philo, "has taken a fork");
}

static void	put_forks(t_philosopher *philo)
{
	printf("Philosopher %d is putting down forks.\n", philo->id);
	pthread_mutex_unlock(philo->left_fork);
	printf("Philosopher %d is putting down forks.\n", philo->id);
	pthread_mutex_unlock(philo->right_fork);
}

static void	eat(t_philosopher *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->death_lock);
	philo->last_meal = get_timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->death_lock);
	print_status(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	put_forks(philo);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->left_fork == philo->right_fork)
	{
		printf("Error: Double fork assigned to %d", philo->id);
		return (NULL);
	}
	while (philo->data->simulation_running)
	{
		eat(philo);
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
