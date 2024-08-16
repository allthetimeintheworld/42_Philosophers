/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:03:16 by jadyar            #+#    #+#             */
/*   Updated: 2024/08/16 16:49:22 by jadyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	bool				eating;
	bool				finished;
	int					meal_count;
	int					prev_meal;
	pthread_t			thread;
	struct s_data		*data;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}						t_philo;

typedef struct s_data
{
	int					num_of_threads;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_required;
	long long			start_time;
	int					simulation_run;
	bool				dead;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		print_lock_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		*forks;
	t_philo				*philo;
}						t_data;

int						main(int ac, char **av);
void					err_msg(char *msg);
void					*monitor(void *arg);
void					turn_dead(t_data *data);
void					init_input(t_data *data, int ac, char **av);
void					init_forks(t_data *data);
void					init_philos(t_data *data);
int						*simulation(t_data *data);
int						init_all(t_data *data, int ac, char **av);
int						check_args(int ac, char **av);
int						ft_is_digit(int c);
int						ft_atoi(const char *str);
int						thread_finished(t_data *data);
long long				get_timestamp(void);
// void					ft_usleep(int time);
int						ft_usleep(size_t miliseconds);
int						death_check(t_data *data);
void					*thread_routine(void *arg);
void					is_sleeping(t_philo *philo);
void					is_thinking(t_philo *philo);
void					is_eating(t_philo *philo);
int						is_num(char *av);
void					print_status(char *status, t_philo *philo);
void					cleanup(t_data *data, char *error_message);

#endif
