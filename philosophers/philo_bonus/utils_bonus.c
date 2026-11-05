/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 20:19:59 by tmura             #+#    #+#             */
/*   Updated: 2026/01/28 10:32:15 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	str_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	put_ll(char *buf, long long n)
{
	char	tmp[32];
	int		i;
	int		j;

	if (n == 0)
	{
		buf[0] = '0';
		return (1);
	}
	i = 0;
	while (n > 0)
	{
		tmp[i++] = (char)('0' + (n % 10));
		n /= 10;
	}
	j = 0;
	while (i > 0)
		buf[j++] = tmp[--i];
	return (j);
}

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "cannot get time\n", 16);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

void	precise_usleep(long long time_in_ms, t_data *data)
{
	long long	start_time;

	(void)data;
	start_time = get_time();
	while (get_time() - start_time < time_in_ms)
	{
		if (time_in_ms - (get_time() - start_time) > 1)
			usleep(100);
	}
}

void	print_action(t_data *data, int id, char *str)
{
	long long	now;
	char		buf[128];
	int			n;
	int			sl;
	int			i;

	sl = str_len(str);
	i = 0;
	sem_wait(data->print_sem);
	now = get_time() - data->start_time;
	n = 0;
	n += put_ll(buf + n, now);
	buf[n++] = ' ';
	n += put_ll(buf + n, (long long)id);
	buf[n++] = ' ';
	while (i < sl)
		buf[n++] = str[i++];
	buf[n++] = '\n';
	write(1, buf, n);
	sem_post(data->print_sem);
}
