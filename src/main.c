/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:04:49 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/16 17:12:54 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_data *data, char *error_message)
{
	int	i;

	i = 0;
	while (i < data->num_of_threads)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->print_lock_mutex);
	free(data->forks);
	free(data->philo);
	if (error_message)
		err_msg(error_message);
}
/* void	cleanup(t_data *data, char *error_message)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->num_of_threads)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philo)
	{
		free(data->philo);
	}
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->print_lock_mutex);
	if (error_message)
	{
		err_msg(error_message);
	}
} */

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 5 || ac > 6)
		err_msg("Number of arguments is invalid");
	if (!check_args(ac, av))
		err_msg("Arg is invalid");
	data = malloc(sizeof(t_data));
	if (data == NULL)
		err_msg("Malloc failed");
	if (init_all(data, ac, av) == 1)
	{
		cleanup(data, "error with initializing");
		free(data);
		return (1);
	}
	simulation(data);
	cleanup(data, NULL);
	free(data);
	return (0);
}
