/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:42:53 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/16 17:10:06 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(char *status, t_philo *philo)
{
	size_t	time;

	if (pthread_mutex_lock(&philo->data->write_mutex) != 0)
		printf("Debug: failed to lock write_lock");
	time = get_timestamp() - philo->data->start_time;
	if (!death_check(philo->data))
		printf("%zu %d %s\n", time, philo->id, status);
	if (pthread_mutex_unlock(&philo->data->write_mutex) != 0)
		printf("Debug: failed to unlock write_lock");
}

int	*simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	data->start_time = get_timestamp();
	if (pthread_create(&monitor_thread, NULL, &monitor, (void *)data) != 0)
	{
		cleanup(data, "Thread creation error: monitor thread");
		//return (1);
	}
	while (i < data->num_of_threads)
	{
		if (pthread_create(&data->philo[i].thread, NULL, thread_routine, \
		&data->philo[i]) != 0)
			cleanup(data, "Thread creation error: Philo thread");
		i++;
	}
	i = 0;
	while (i < data->num_of_threads)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			cleanup(data, "Thread join error: philo thread");
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		cleanup(data, "Thread join error: monitor thread");
	return (0);
}
