/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 20:17:55 by tmura             #+#    #+#             */
/*   Updated: 2026/01/19 14:46:00 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	die_check(t_philo *philo, t_data *data)
{
	long long	time;
	int			i;

	time = get_time() - philo->last_meal_time;
	if (time > data->time_to_die)
	{
		sem_post(philo->meal_lock);
		sem_wait(data->print_sem);
		printf("%lld %d died\n", get_time() - data->start_time, philo->id);
		i = 0;
		while (i < data->num_philos)
		{
			sem_post(data->dead_sem);
			i++;
		}
		exit(1);
	}
	sem_post(philo->meal_lock);
	usleep(500);
}

void	*monitor(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		sem_wait(philo->meal_lock);
		if (data->num_meals != -1 && philo->meals_eaten >= data->num_meals)
		{
			sem_post(philo->meal_lock);
			break ;
		}
		die_check(philo, data);
	}
	return (NULL);
}
