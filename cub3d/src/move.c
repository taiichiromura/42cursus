/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:33:08 by tmura             #+#    #+#             */
/*   Updated: 2026/05/12 14:33:08 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc_move_amount(t_data *data)
{
	double	speed;

	speed = 0.05;
	data->dx = 0;
	data->dy = 0;
	if (data->flg.key_w)
	{
		data->dx += data->dir_x * speed;
		data->dy += data->dir_y * speed;
	}
	if (data->flg.key_s)
	{
		data->dx -= data->dir_x * speed;
		data->dy -= data->dir_y * speed;
	}
	if (data->flg.key_a)
	{
		data->dx += data->dir_y * speed;
		data->dy -= data->dir_x * speed;
	}
	if (data->flg.key_d)
	{
		data->dx -= data->dir_y * speed;
		data->dy += data->dir_x * speed;
	}
}

void	rotate_right(t_data *data, double *rot_speed,
					double *old_dir_x, double *old_planet_x)
{
	*old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(*rot_speed)
		- data->dir_y * sin(*rot_speed);
	data->dir_y = *old_dir_x * sin(*rot_speed)
		+ data->dir_y * cos(*rot_speed);
	*old_planet_x = data->plane_x;
	data->plane_x = data->plane_x * cos(*rot_speed)
		- data->plane_y * sin(*rot_speed);
	data->plane_y = *old_planet_x * sin(*rot_speed)
		+ data->plane_y * cos(*rot_speed);
}

void	rotate_left(t_data *data, double *rot_speed,
					double *old_dir_x, double *old_planet_x)
{
	*old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(-*rot_speed)
		- data->dir_y * sin(-*rot_speed);
	data->dir_y = *old_dir_x * sin(-*rot_speed)
		+ data->dir_y * cos(-*rot_speed);
	*old_planet_x = data->plane_x;
	data->plane_x = data->plane_x * cos(-*rot_speed)
		- data->plane_y * sin(-*rot_speed);
	data->plane_y = *old_planet_x * sin(-*rot_speed)
		+ data->plane_y * cos(-*rot_speed);
}

void	rotate(t_data *data)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_planet_x;

	rot_speed = 0.005;
	if (data->flg.key_right)
		rotate_right(data, &rot_speed, &old_dir_x, &old_planet_x);
	if (data->flg.key_left)
		rotate_left(data, &rot_speed, &old_dir_x, &old_planet_x);
}

int	move(t_data *data)
{
	calc_move_amount(data);
	check_wall_exit(data);
	rotate(data);
	if (data->flg.key_esc)
	{
		free_exit(data, 0, "esc pushed\n");
	}
	return (0);
}
