/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:47:23 by tmura             #+#    #+#             */
/*   Updated: 2026/01/27 16:47:23 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	someone_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->death_lock);
	dead = data->someone_dead;
	pthread_mutex_unlock(&data->death_lock);
	return (dead);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!someone_dead(philo->data))
	{
		if (philo->id % 2 == 0)
			usleep(1000);
		if (take_fork(philo))
			break ;
		eat(philo);
		put_fork(philo);
		take_nap(philo);
		think(philo);
	}
	return (NULL);
}

int	run_simulation(t_data *data, t_philo *philos)
{
	int			i;
	pthread_t	observer;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	if (pthread_create(&observer, NULL, monitor, philos) != 0)
		destroy_mutex(data, philos);
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destroy_mutex(data, philos);
	while (i < data->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;

	if (argc < 5 || argc > 6)
		return (1);
	if (check_input(argv) || init_all(&data, argc, argv, &philos))
		return (1);
	if (run_simulation(&data, philos))
	{
		destroy_mutex(&data, philos);
		return (1);
	}
	destroy_mutex(&data, philos);
	return (0);
}
