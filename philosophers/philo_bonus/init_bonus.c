/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 20:17:45 by tmura             #+#    #+#             */
/*   Updated: 2026/01/28 11:42:05 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_meals = -1;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	data->dead_flag = false;
	data->forks = NULL;
	data->print_sem = NULL;
	data->dead_sem = NULL;
	data->pids = NULL;
	if (data->num_philos < 1)
		return (error_msg("Invalid number of philosophers"));
	if (data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (error_msg("Invalid time values"));
	if (argc == 6 && data->num_meals < 1)
		return (error_msg("Invalid number of meals"));
	return (0);
}

int	init_semaphores(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/dead");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->num_philos);
	data->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	data->dead_sem = sem_open("/dead", O_CREAT, 0644, 0);
	if (data->forks == SEM_FAILED || data->print_sem == SEM_FAILED
		|| data->dead_sem == SEM_FAILED)
		return (error_msg("Semaphore initialization failed"));
	return (0);
}

int	init_philos(t_data *data)
{
	int		i;
	char	name[32];

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		make_sem_name(name, i + 1);
		sem_unlink(name);
		data->philos[i].meal_lock = sem_open(name, O_CREAT, 0644, 1);
		if (data->philos[i].meal_lock == SEM_FAILED)
			return (error_msg("Semaphore initialization failed"));
		i++;
	}
	data->pids = malloc(sizeof(pid_t) * data->num_philos);
	if (!data->pids)
		return (error_msg("Memory allocation failed"));
	memset(data->pids, 0, sizeof(pid_t) * data->num_philos);
	return (0);
}
