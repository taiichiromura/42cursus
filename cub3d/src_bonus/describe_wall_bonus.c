/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   describe_wall_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:03:03 by tmura             #+#    #+#             */
/*   Updated: 2026/05/16 17:03:03 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	describe_wall1(t_data *data)
{
	if (data->dda.side == 0)
		data->dda.perp_wall_dist
			= (data->dda.side_dist_x - data->dda.delta_dist_x);
	else
		data->dda.perp_wall_dist
			= (data->dda.side_dist_y - data->dda.delta_dist_y);
	data->dda.line_height = (int)(SCREEN_HEIGHT / data->dda.perp_wall_dist);
	data->dda.draw_start = -data->dda.line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->dda.draw_start < 0)
		data->dda.draw_start = 0;
	data->dda.draw_end = data->dda.line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->dda.draw_end >= SCREEN_HEIGHT)
		data->dda.draw_end = SCREEN_HEIGHT - 1;
}

void	describe_wall2(t_data *data)
{
	if (data->dda.side == 0)
	{
		if (data->dda.ray_dir_x < 0)
			data->dda.tex_num = 2;
		else
			data->dda.tex_num = 3;
	}
	else
	{
		if (data->dda.ray_dir_y < 0)
			data->dda.tex_num = 0;
		else
			data->dda.tex_num = 1;
	}
	if (data->dda.hit == 2)
		data->dda.tex_num = 4;
}

void	describe_wall3(t_data *data)
{
	if (data->dda.side == 0)
		data->dda.wall_x
			= data->pos_y + data->dda.perp_wall_dist * data->dda.ray_dir_y;
	else
		data->dda.wall_x
			= data->pos_x + data->dda.perp_wall_dist * data->dda.ray_dir_x;
	data->dda.wall_x -= floor(data->dda.wall_x);
	data->dda.tex_x = (int)(data->dda.wall_x * (double) 64);
	if (data->dda.side == 0 && data->dda.ray_dir_x < 0)
		data->dda.tex_x = 64 - data->dda.tex_x - 1;
	if (data->dda.side == 1 && data->dda.ray_dir_y > 0)
		data->dda.tex_x = 64 - data->dda.tex_x - 1;
	data->dda.step = 1.0 * 64 / data->dda.line_height;
	data->dda.tex_pos = (data->dda.draw_start - SCREEN_HEIGHT
			/ 2 + data->dda.line_height / 2) * data->dda.step;
}

void	describe_wall4(t_data *data, const int x)
{
	int	y;
	int	color;

	y = data->dda.draw_start;
	while (y < data->dda.draw_end)
	{
		data->dda.tex_y = (int) data->dda.tex_pos & (64 - 1);
		data->dda.tex_pos += data->dda.step;
		if (data->dda.tex_y < 0)
			data->dda.tex_y = 0;
		color = get_pixel_color(&data->tex[data->dda.tex_num],
				data->dda.tex_x, data->dda.tex_y);
		if (data->dda.side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
	data->z_buffer[x] = data->dda.perp_wall_dist;
}

void	check_wall_exit(t_data *data)
{
	double	margin_x;
	double	margin_y;

	if (data->dx >= 0)
		margin_x = 0.2;
	else
		margin_x = -0.2;
	if (data->dy >= 0)
		margin_y = 0.2;
	else
		margin_y = -0.2;
	if (data->map[(int)data->pos_y][(int)(data->pos_x + data->dx + margin_x)]
		!= '1'
		&& data->map[(int)data->pos_y][(int)(data->pos_x + data->dx + margin_x)]
		!= 'D')
		data->pos_x += data->dx;
	if (data->map[(int)(data->pos_y + data->dy + margin_y)][(int) data->pos_x]
		!= '1'
		&&
		data->map[(int)(data->pos_y + data->dy + margin_y)][(int) data->pos_x]
		!= 'D')
		data->pos_y += data->dy;
}
