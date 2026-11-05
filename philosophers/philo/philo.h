/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:28:34 by tmura             #+#    #+#             */
/*   Updated: 2026/01/26 15:28:34 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stddef.h>

typedef struct s_data
{
	pthread_mutex_t			death_lock;
	pthread_mutex_t			print_lock;
	pthread_mutex_t			*forks;
	long long				time_to_die;
	long long				time_to_sleep;
	long long				time_to_eat;
	int						num_philos;
	int						someone_dead;
	int						num_meals;
	long long				start_time;
}	t_data;

typedef struct s_philo
{
	pthread_t					thread;
	pthread_mutex_t				*left_fork;
	pthread_mutex_t				*right_fork;
	pthread_mutex_t				meal_lock;

	int							id;
	long long					last_meal;
	int							meal_num;
	t_data						*data;
}	t_philo;

long long						get_current_time(void);
void							smart_sleep(long long time_to_sleep);
int								init_data(t_data *data, int argc, char **argv);
int								init_forks(t_data *data);
int								init_philos(t_data *data, t_philo *philo);
void							philo_died(t_philo *philo);
int								dead_check(t_philo *philo);
int								check_philos(t_philo *philos);
void							*monitor(void *arg);
int								take_fork(t_philo *philo);
void							put_fork(t_philo *philo);
void							eat(t_philo *philo);
int								someone_dead(t_data *data);
void							*routine(void *arg);
int								ft_strlen(char *str);
int								ft_atoi(char *str);
int								check_input(char **argv);
int								check_arg_content(char *arg);
void							destroy_mutex(t_data *data, t_philo *philos);
void							print_status(t_philo *philo, char *msg);
void							take_nap(t_philo *philo);
int								init_all(t_data *data, int argc,
									char **argv, t_philo **philos);
void							think(t_philo *philo);
#endif
