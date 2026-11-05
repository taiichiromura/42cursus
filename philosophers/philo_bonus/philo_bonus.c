/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 20:18:10 by tmura             #+#    #+#             */
/*   Updated: 2026/01/28 14:40:15 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup(t_data *data)
{
	if (data->forks)
		sem_close(data->forks);
	if (data->print_sem)
		sem_close(data->print_sem);
	if (data->dead_sem)
		sem_close(data->dead_sem);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/dead");
	clean_up_philos(data);
	if (data->pids)
		free(data->pids);
}

void	kill_all_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (data->pids[i] != 0 && kill(data->pids[i], 0) == 0)
			kill(data->pids[i], SIGKILL);
		i++;
	}
}

int	wait_for_processes(t_data *data)
{
	int		i;
	int		status;
	int		dead_found;
	pid_t	pid;

	dead_found = 0;
	i = 0;
	while (i < data->num_philos)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			if (!dead_found)
			{
				kill_all_processes(data);
				dead_found = 1;
			}
		}
		i++;
	}
	return (0);
}

static int	init(t_data	*data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_msg("Usage: ./philo_bonus number_of_philosophers "
				"time_to_die time_to_eat time_to_sleep "
				"[number_of_times_each_philosopher_must_eat]"));
	if (init_data(data, argc, argv) != 0)
		return (1);
	if (init_semaphores(data) != 0)
		return (1);
	if (init_philos(data) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;

	if (init(&data, argc, argv))
		return (1);
	data.start_time = get_time();
	i = 0;
	while (i < data.num_philos)
	{
		data.pids[i] = fork();
		if (data.pids[i] == 0)
		{
			philo_routine(&data.philos[i]);
			exit(0);
		}
		else if (data.pids[i] < 0)
		{
			kill_all_processes(&data);
			return (error_msg("Fork failed"));
		}
		i++;
	}
	wait_for_processes(&data);
	cleanup(&data);
	return (0);
}
