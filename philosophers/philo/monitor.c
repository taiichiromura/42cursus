/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:31:29 by tmura             #+#    #+#             */
/*   Updated: 2026/01/26 16:31:29 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_died(t_philo *philo)
{
	long long	time;

	time = 0;
	pthread_mutex_lock(&philo->data->death_lock);
	if (!philo->data->someone_dead)
	{
		philo->data->someone_dead = 1;
		pthread_mutex_lock(&philo->data->print_lock);
		time = get_current_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id, "died");
		pthread_mutex_unlock(&philo->data->print_lock);
		pthread_mutex_unlock(&philo->data->death_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	return ;
}

int	dead_check(t_philo *philo)
{
	long long	last_meal_time;

	pthread_mutex_lock(&philo->meal_lock);
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	if (get_current_time() - last_meal_time >= philo->data->time_to_die)
		return (1);
	return (0);
}

int	check_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->num_philos)
	{
		if (dead_check(&philos[i]))
		{
			philo_died(&philos[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	all_ate(t_philo *philos)
{
	int		i;
	int		finished_philos;

	i = 0;
	finished_philos = 0;
	while (i < philos->data->num_philos)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		if (philos[i].meal_num >= philos->data->num_meals)
			finished_philos++;
		pthread_mutex_unlock(&philos[i].meal_lock);
		i++;
	}
	if (finished_philos == philos->data->num_philos)
	{
		pthread_mutex_lock(&philos->data->death_lock);
		philos->data->someone_dead = 1;
		pthread_mutex_unlock(&philos->data->death_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo		*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (check_philos(philos))
			break ;
		if (philos->data->num_meals >= 1)
		{
			if (all_ate(philos))
				break ;
		}
		usleep(500);
	}
	return (NULL);
}
