/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:30:47 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/14 18:02:03 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Initialize mutexes for forks and philosopher attributes
static int	init_forks(t_data *data, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (1);
		}
		philosophers[i].id = i + 1;
		philosophers[i].meals_eaten = 0;
		philosophers[i].is_eating = 0;
		philosophers[i].data = data;
		philosophers[i].finished_eating = 0;
		philosophers[i].last_meal = get_timestamp();
		philosophers[i].left_fork = &data->forks[i];
		philosophers[i].right_fork = &data->forks[(i + 1) \
			% data->num_philosophers];
		printf("Initialized philosopher %d: id=%d, left_fork=%p, \
		right_fork=%p, data=%p\n",
			i, philosophers[i].id, (void*)philosophers[i].left_fork, \
		(void*)philosophers[i].right_fork, (void*)philosophers[i].data);
		i++;
	}
	return (0);
}

// Initialize the simulation
int	init_simulation(t_data *data, t_philosopher **philosophers)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
		return (1);
	*philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	if (!*philosophers)
	{
		free(data->forks);
		return (1);
	}
	if (init_forks(data, *philosophers) != 0)
	{
		free(*philosophers);
		free(data->forks);
		return (1);
	}
	if (pthread_mutex_init(&data->print_lock, NULL) != 0 || \
		pthread_mutex_init(&data->death_lock, NULL) != 0)
	{
		free(*philosophers);
		free(data->forks);
		return (1);
	}
	data->simulation_running = 1;
	return (0);
}

// Create philosopher threads
int	create_philosophers(t_data *data, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&philosophers[i].thread, NULL, philosopher_routine,
				&philosophers[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(philosophers[i].thread, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

// Join philosopher threads and cleanup
void	join_philosophers(t_data *data, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
	free(philosophers);
	free(data->forks);
}
