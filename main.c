/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:30:49 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/14 14:46:22 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosopher	*philosophers;
	pthread_t		monitor_thread;

	if (parse_args(argc, argv, &data) != 0)
		return (1);
	if (init_simulation(&data, &philosophers) != 0)
		return (1);
	if (create_philosophers(&data, philosophers) != 0)
		return (1);
	if (pthread_create(&monitor_thread, NULL, monitor_philosophers, &data) != 0)
		return (1);
	join_philosophers(&data, philosophers);
	pthread_join(monitor_thread, NULL);
	free(philosophers);
	free(data.forks);
	return (0);
}
