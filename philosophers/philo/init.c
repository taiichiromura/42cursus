/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:13:55 by tmura             #+#    #+#             */
/*   Updated: 2026/01/27 16:13:55 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_meals = -1;
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	data->someone_dead = 0;
	data->start_time = get_current_time();
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = data->start_time;
		philo[i].meal_num = 0;
		philo[i].data = data;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		pthread_mutex_init(&philo[i].meal_lock, NULL);
		i++;
	}
	return (0);
}

int	init_all(t_data *data, int argc, char **argv, t_philo **philos)
{
	if (init_data(data, argc, argv))
		return (1);
	if (init_forks(data))
		return (1);
	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos || init_philos(data, *philos))
		return (1);
	return (0);
}
