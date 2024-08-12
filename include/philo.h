/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:10:14 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/12 15:09:16 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define INCORRECT_INPUT 1

# define TAKE_FORKS "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIED "died"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	int					number_of_meals;
	int					philo_full;
	int					philo_dead;
	long				start_time;
	pthread_t			monitor;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		full;
	t_philo				*philos;
	int					she_died;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					left_fork;
	int					right_fork;
	int					eat_count;
	long				last_eat;
	pthread_t			thread;
	struct s_data		*data;
}						t_philo;

int						ft_atoi(const char *str);
int						is_digit(char c);
void					*philo_routine(void *arg);
int						ft_usleep(long time);
int						err_msg(char *err_msg);
long long				get_time(void);
void					*monitor_routine(void *arg);
void					print_status(t_philo *philo, char *status);
void					cleanup(t_data *data);
void					start_mon(t_data *data);
int						start_sim(t_philo *philo, t_data *data);
int						init_data(t_data *data, int ac, char **av);
int						init_philos(t_philo *philo, t_data *data);
int						init_rest(t_data *data);
#endif
