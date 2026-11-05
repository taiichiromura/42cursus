/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   rendering.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: t.mura <t.mura@student.42tokyo.jp>        #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/05/06 16:46:21 by t.mura           #+#    #+#              */
/*   Updated: 2026/05/11 22:32:35 by t.mura          ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	mouse_move(int x, int y, t_data *data)
{
	double		rot_speed;
	double		old_dir_x;
	double		old_planet_x;
	static int	last_x = -1;

	(void)y;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	rot_speed = (x - last_x) * 0.01;
	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(rot_speed) - data->dir_y * sin(rot_speed);
	data->dir_y = old_dir_x * sin(rot_speed) + data->dir_y * cos(rot_speed);
	old_planet_x = data->plane_x;
	data->plane_x = data->plane_x * cos(rot_speed)
		- data->plane_y * sin(rot_speed);
	data->plane_y = old_planet_x * sin(rot_speed)
		+ data->plane_y * cos(rot_speed);
	last_x = x;
	return (0);
}

unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= 64 || y < 0 || y >= 64)
		return (0);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *) dst);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = (char *) data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	render_frame(t_data *data)
{
	int	x;

	put_sail_floor(data);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		set_dir(data, x);
		calc_dist_to_wall(data);
		dda(data);
		describe_wall1(data);
		describe_wall2(data);
		describe_wall3(data);
		describe_wall4(data, x);
		x++;
	}
	draw_minimap(data);
	if (data->sprite.exist)
		render_sprites(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
