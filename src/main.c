/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:23:48 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/09 12:57:59 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_status(t_philo *philo, char *status)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->write_lock);
	if (!data->she_died)
		printf("%lld %d %s\n", get_time() - data->start_time, \
			philo->id + 1, status);
	pthread_mutex_unlock(&data->write_lock);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	//data = (t_data){0};
	if (ac < 5 || ac > 6)
		err_msg("Invalid arguments");
	if (init_data(&data, ac, av))
		err_msg("Invalid arguments");
	philo = malloc(sizeof(t_philo) * data.philo_count);
	if (!philo)
		err_msg("Error: Malloc failed\n");
	if (init_philos(philo, &data))
		err_msg("Error: Malloc failed\n");
	if (start_sim(philo, &data))
		err_msg("Error: Sim not successful\n");
	cleanup(&data);
	free(philo);
	return (0);
}
