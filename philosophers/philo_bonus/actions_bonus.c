/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 20:17:41 by tmura             #+#    #+#             */
/*   Updated: 2026/01/28 14:56:18 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->num_philos == 1)
	{
		sem_wait(data->forks);
		print_action(data, philo->id, "has taken a fork");
		usleep(data->time_to_die * 1000);
		sem_wait(data->print_sem);
		printf("%lld %d died\n", get_time() - data->start_time, philo->id);
		sem_post(data->dead_sem);
		exit(1);
	}
	sem_wait(data->forks);
	print_action(data, philo->id, "has taken a fork");
	sem_wait(data->forks);
	print_action(data, philo->id, "has taken a fork");
	print_action(data, philo->id, "is eating");
	sem_wait(philo->meal_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	sem_post(philo->meal_lock);
	precise_usleep(data->time_to_eat, data);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	sleep_think(t_philo *philo)
{
	t_data		*data;
	long long	think_time;

	data = philo->data;
	print_action(data, philo->id, "is sleeping");
	precise_usleep(data->time_to_sleep, data);
	print_action(data, philo->id, "is thinking");
	if (data->num_philos % 2 != 0)
	{
		think_time = (data->time_to_die
				- (data->time_to_eat + data->time_to_sleep)) / 2;
		if (think_time > 0)
			usleep(think_time * 1000);
	}
}
