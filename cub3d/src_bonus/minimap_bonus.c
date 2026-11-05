/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:02:19 by tmura             #+#    #+#             */
/*   Updated: 2026/05/16 17:02:19 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->minimap.size)
	{
		j = 0;
		while (j < data->minimap.size)
		{
			if (x + i >= 0 && x + i < SCREEN_WIDTH
				&& y + j >= 0 && y + j < SCREEN_HEIGHT)
			{
				my_mlx_pixel_put(data, x + i, y + j, color);
			}
			j++;
		}
		i++;
	}
}

void	draw_point(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (x + i >= 0 && x + i < SCREEN_WIDTH
				&& y + j >= 0 && y + j < SCREEN_HEIGHT)
			{
				my_mlx_pixel_put(data, x + i, y + j, color);
			}
			j++;
		}
		i++;
	}
}

void	draw_width(t_data *data, int x, int y, int color)
{
	while (x < data->map_width)
	{
		color = 0x000000;
		draw_square(data, x * data->minimap.size + 20,
			y * data->minimap.size + 20, color);
		x++;
	}
}

void	draw_minimap(t_data *data)
{
	int	color;
	int	x;
	int	y;

	data->minimap.size = 5;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width && data->map[y][x] != '\0')
		{
			if (data->map[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x000000;
			draw_square(data, x * data->minimap.size + 20,
				y * data->minimap.size + 20, color);
			x++;
		}
		draw_width(data, x, y, color);
		y++;
	}
	draw_point(data, data->pos_x * data->minimap.size + 20,
		data->pos_y * data->minimap.size + 20, 0xFF0000);
}
