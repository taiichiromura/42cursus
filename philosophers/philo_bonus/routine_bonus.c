/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 20:22:23 by tmura             #+#    #+#             */
/*   Updated: 2026/01/19 15:20:50 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_watcher(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	sem_wait(data->dead_sem);
	exit(1);
	return (NULL);
}

static void	philo_cycle(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	while (1)
	{
		sem_wait(philo->meal_lock);
		if (data->num_meals != -1 && philo->meals_eaten >= data->num_meals)
		{
			sem_post(philo->meal_lock);
			break ;
		}
		sem_post(philo->meal_lock);
		eat(philo);
		sleep_think(philo);
	}
}

void	philo_routine(t_philo *philo)
{
	t_data		*data;
	pthread_t	monitor_thread;
	pthread_t	death_watcher_thread;

	data = philo->data;
	sem_wait(philo->meal_lock);
	philo->last_meal_time = data->start_time;
	sem_post(philo->meal_lock);
	if (pthread_create(&monitor_thread, NULL, monitor, philo) != 0)
		exit(1);
	if (pthread_create(&death_watcher_thread, NULL, death_watcher, philo) != 0)
		exit(1);
	pthread_detach(monitor_thread);
	pthread_detach(death_watcher_thread);
	if (philo->id % 2 == 0)
		usleep(500);
	philo_cycle(philo);
	exit(0);
}
