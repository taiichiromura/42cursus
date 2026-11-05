/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   key_press.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: t.mura <t.mura@student.42tokyo.jp>        #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/05/09 19:42:30 by t.mura           #+#    #+#              */
/*   Updated: 2026/05/10 23:01:41 by t.mura          ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parse_rgb(char *str)
{
	char	**colors;
	int		r;
	int		g;
	int		b;

	colors = ft_split(str, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
		return (ERROR);
	if (ft_is_space(colors[0]) || ft_is_space(colors[1])
		|| ft_is_space(colors[2]))
	{
		free_stab(colors);
		return (ERROR);
	}
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r < 0 || r > MAX_RGB || g < 0 || g > MAX_RGB || b < 0 || b > MAX_RGB)
	{
		free_stab(colors);
		return (ERROR);
	}
	free_stab(colors);
	return (r << 16 | g << 8 | b);
}

int	in_map(t_data *data)
{
	if (*data->trimmed == '1' || *data->trimmed == '0'
		|| *data->trimmed == 'D')
		return (1);
	return (0);
}

int	parse_config_line(char *line, t_data *data)
{
	data->trimmed = line;
	while (*data->trimmed && (*data->trimmed == ' '
			|| (*data->trimmed >= 9 && *data->trimmed <= 13)))
		data->trimmed++;
	if (*data->trimmed == '\0' || *data->trimmed == '\n')
		return (1);
	if (ft_strncmp(data->trimmed, "NO ", 3) == 0)
		set_north_path(data, data->trimmed);
	else if (ft_strncmp(data->trimmed, "SO ", 3) == 0)
		set_south_path(data, data->trimmed);
	else if (ft_strncmp(data->trimmed, "WE ", 3) == 0)
		set_west_path(data, data->trimmed);
	else if (ft_strncmp(data->trimmed, "EA ", 3) == 0)
		set_east_path(data, data->trimmed);
	else if (ft_strncmp(data->trimmed, "F ", 2) == 0)
		set_floor_color(data, data->trimmed);
	else if (ft_strncmp(data->trimmed, "C ", 2) == 0)
		set_ceiling_color(data, data->trimmed);
	else if (in_map(data))
		data->map_info.in_map = 1;
	else
		free_exit(data, PARSE_FAILED, data->map_info.line);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == K_W)
		data->flg.key_w = 1;
	if (keycode == K_A)
		data->flg.key_a = 1;
	if (keycode == K_D)
		data->flg.key_d = 1;
	if (keycode == K_S)
		data->flg.key_s = 1;
	if (keycode == K_E)
	{
		open_close_door(data);
	}
	if (keycode == K_RIGHT)
		data->flg.key_right = 1;
	if (keycode == K_LEFT)
		data->flg.key_left = 1;
	if (keycode == K_ESC)
		data->flg.key_esc = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == K_W)
		data->flg.key_w = 0;
	if (keycode == K_A)
		data->flg.key_a = 0;
	if (keycode == K_D)
		data->flg.key_d = 0;
	if (keycode == K_S)
		data->flg.key_s = 0;
	if (keycode == K_RIGHT)
		data->flg.key_right = 0;
	if (keycode == K_LEFT)
		data->flg.key_left = 0;
	if (keycode == K_ESC)
		data->flg.key_esc = 0;
	return (0);
}
