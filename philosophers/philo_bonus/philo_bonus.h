/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 20:23:04 by tmura             #+#    #+#             */
/*   Updated: 2026/01/28 14:40:03 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include <pthread.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pid_t			pid;
	sem_t			*meal_lock;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	bool			dead_flag;
	long long		start_time;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*dead_sem;
	t_philo			*philos;
	pid_t			*pids;
}	t_data;

long long	get_time(void);
void		precise_usleep(long long time_in_ms, t_data *data);
void		print_action(t_data *data, int id, char *str);
int			ft_atoi(const char *str);
int			error_msg(char *str);
void		make_sem_name(char *name, int id);
int			init_data(t_data *data, int argc, char **argv);
int			init_philos(t_data *data);
int			init_semaphores(t_data *data);
void		eat(t_philo *philo);
void		sleep_think(t_philo *philo);
void		*monitor(void *arg);
void		philo_routine(t_philo *philo);
void		clean_up_philos(t_data *data);

#endif
