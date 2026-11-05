/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:10:09 by tmura             #+#    #+#             */
/*   Updated: 2026/05/12 16:10:09 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_wall(t_data *data, char **map, int h, int w)
{
	if (h < 0 || h >= data->map_height)
		free_stab_exit(data, map, FAILED, "Map is open");
	if (!map[h])
		free_stab_exit(data, map, FAILED, "Map does not exitst!");
	data->map_info.tmp_width = (int)ft_strlen(map[h]);
	if (w < 0 || !map[h] || w >= data->map_info.tmp_width)
		free_stab_exit(data, map, FAILED, "Map is open!");
	if (is_space(map[h][w]))
		free_stab_exit(data, map, FAILED, "space in the map!");
	if (!(map[h][w] == 'v' || map[h][w] == '1'
			|| map[h][w] == '0'))
		free_stab_exit(data, map, FAILED, "invalid letter!");
	if (map[h][w] == '1' || map[h][w] == 'v')
		return ;
	map[h][w] = 'v';
	check_wall(data, map, h + 1, w);
	check_wall(data, map, h - 1, w);
	check_wall(data, map, h, w + 1);
	check_wall(data, map, h, w - 1);
}

int	check_characters(t_data *data)
{
	char	position;

	while (data->pointer.h < data->map_height)
	{
		data->pointer.w = 0;
		while (data->pointer.w < data->map_width
			&& data->map[data->pointer.h][data->pointer.w] != '\0')
		{
			position = data->map[data->pointer.h][data->pointer.w];
			if (position == 'N' || position == 'S'
				|| position == 'W' || position == 'E')
				set_player_position(data);
			if (position == 'K')
				set_sprite_position(data);
			data->pointer.w++;
		}
		data->pointer.h++;
	}
	if (data->pointer.cnt != 1)
	{
		return (1);
	}
	else
		return (0);
}

void	check_valid_letter(t_data *data, char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(data->map[y]))
		{
			if (!(map[y][x] == '0' || is_space_and_crlf(map[y][x])
					|| map[y][x] == '1'))
				free_stab_exit(data, map, FAILED, "invalid letter!");
			x++;
		}
		y++;
	}
}

int	check_character_and_wall(t_data *data)
{
	if (check_characters(data) != 0)
	{
		free_exit(data, FAILED, "check_characters failed!");
		return (1);
	}
	data->cmap = copy_map(data);
	check_valid_letter(data, data->cmap);
	check_wall(data, data->cmap,
		data->pos_y, data->pos_x);
	free_stab(data->cmap);
	return (0);
}
