/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:35:52 by tmura             #+#    #+#             */
/*   Updated: 2026/05/12 17:35:52 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_dir(t_data *data, const int x)
{
	data->dda.camera_x = 2 * x / (double) SCREEN_WIDTH - 1;
	data->dda.ray_dir_x = data->dir_x + data->plane_x * data->dda.camera_x;
	data->dda.ray_dir_y = data->dir_y + data->plane_y * data->dda.camera_x;
	if (data->dda.ray_dir_x == 0)
		data->dda.delta_dist_x = 1e30;
	else
		data->dda.delta_dist_x = fabs(1 / data->dda.ray_dir_x);
	if (data->dda.ray_dir_y == 0)
		data->dda.delta_dist_y = 1e30;
	else
		data->dda.delta_dist_y = fabs(1 / data->dda.ray_dir_y);
	data->dda.map_x = (int) data->pos_x;
	data->dda.map_y = (int) data->pos_y;
}

void	type_of_content(t_data *data)
{
	if (data->dda.map_x >= 0 && data->dda.map_x < data->map_width
		&& data->dda.map_y >= 0 && data->dda.map_y < data->map_height)
	{
		if (data->map[data->dda.map_y][data->dda.map_x] == '1')
			data->dda.hit = 1;
		else if (data->map[data->dda.map_y][data->dda.map_x] == 'D')
			data->dda.hit = 2;
	}
	else
		data->dda.hit = 0;
}

void	dda(t_data *data)
{
	data->dda.hit = 0;
	while (data->dda.hit == 0)
	{
		if (data->dda.side_dist_x < data->dda.side_dist_y)
		{
			data->dda.side_dist_x += data->dda.delta_dist_x;
			data->dda.map_x += data->dda.step_x;
			data->dda.side = 0;
		}
		else
		{
			data->dda.side_dist_y += data->dda.delta_dist_y;
			data->dda.map_y += data->dda.step_y;
			data->dda.side = 1;
		}
		type_of_content(data);
	}
}

void	calc_dist_to_wall(t_data *data)
{
	if (data->dda.ray_dir_x < 0)
	{
		data->dda.step_x = -1;
		data->dda.side_dist_x
			= (data->pos_x - data->dda.map_x) * data->dda.delta_dist_x;
	}
	else
	{
		data->dda.step_x = 1;
		data->dda.side_dist_x
			= (data->dda.map_x + 1.0 - data->pos_x) * data->dda.delta_dist_x;
	}
	if (data->dda.ray_dir_y < 0)
	{
		data->dda.step_y = -1;
		data->dda.side_dist_y
			= (data->pos_y - data->dda.map_y) * data->dda.delta_dist_y;
	}
	else
	{
		data->dda.step_y = 1;
		data->dda.side_dist_y
			= (data->dda.map_y + 1.0 - data->pos_y) * data->dda.delta_dist_y;
	}
}
