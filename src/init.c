/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:04:39 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/16 16:30:16 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_input(t_data *data, int ac, char **av)
{
	data->num_of_threads = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meals_required = -1;
	if (ac == 6)
		data->meals_required = ft_atoi(av[5]);
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_threads);
	if (data->forks == NULL)
	{
		err_msg("Failed to allocate memory for forks");
	}
	while (i < data->num_of_threads)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			err_msg("Failed to init fork mutex");
		}
		i++;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_threads)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meal_count = 0;
		data->philo[i].eating = false;
		data->philo[i].data = data;
		data->philo[i].finished = false;
		data->philo[i].prev_meal = get_timestamp();
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) \
			% data->num_of_threads];
		i++;
	}
}

int	init_all(t_data *data, int ac, char **av)
{
	init_input(data, ac, av);
	data->philo = malloc(sizeof(t_philo) * data->num_of_threads);
	if (data->philo == NULL)
		return (1);
	init_forks(data);
	init_philos(data);
	data->dead = false;
	data->start_time = 0;
	if (pthread_mutex_init(&(data->write_mutex), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(data->print_lock_mutex), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(data->death_mutex), NULL) != 0)
		return (1);
	return (0);
}
