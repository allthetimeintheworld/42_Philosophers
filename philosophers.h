/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:31:43 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/14 18:02:51 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	long			last_meal;
	int				meals_eaten;
	bool			is_eating;
	bool			finished_eating;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}					t_philosopher;

typedef struct s_data
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	int				simulation_running;
	long			start_time;
	t_philosopher	*philosophers;
}					t_data;

int					init_simulation(t_data *data, t_philosopher **philosophers);
void				*philosopher_routine(void *arg);
long				get_timestamp(void);
int					create_philosophers(t_data *data, t_philosopher *philosophers);;
void				join_philosophers(t_data *data, t_philosopher *philosophers);
void				print_status(t_philosopher *philo, const char *status);
long				get_timestamp(void);
void				*monitor_philosophers(void *arg);
int					parse_args(int argc, char **argv, t_data *data);

#endif
