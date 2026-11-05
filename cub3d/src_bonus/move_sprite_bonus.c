/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:01:57 by tmura             #+#    #+#             */
/*   Updated: 2026/05/16 17:01:57 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	update_sprite_animation(t_data *data)
{
	data->sprite.frame_counter++;
	if (data->sprite.frame_counter >= 15)
	{
		data->sprite.frame_counter = 0;
		data->sprite.current_frame++;
		if (data->sprite.current_frame >= 10)
			data->sprite.current_frame = 0;
	}
}

void	check_death(t_data *data)
{
	double	dist;

	dist = sqrt(pow(data->pos_x - data->sprite.x, 2)
			+ pow(data->pos_y - data->sprite.y, 2));
	if (dist < 0.4)
		free_exit(data, FAILED, "KILLED BY BARREL!\n");
}

void	move_to_camera(t_data *data, int *tmp, int *tmp_y)
{
	if (data->map[(int) data->sprite.y][*tmp] != '1' &&
		data->map[(int) data->sprite.y][*tmp] != 'D')
		data->sprite.x = data->sprite.next_x;
	data->sprite.next_y = data->sprite.y;
	if (data->sprite.y < data->pos_y)
		data->sprite.next_y += data->sprite.enemy_speed;
	else
		data->sprite.next_y -= data->sprite.enemy_speed;
	if (data->sprite.next_y > data->sprite.y)
		*tmp_y = (int)(data->sprite.next_y + data->sprite.buffer);
	else
		*tmp_y = (int)(data->sprite.next_y - data->sprite.buffer);
	if (data->map[*tmp_y][(int) data->sprite.x] != '1' &&
			data->map[*tmp_y][(int) data->sprite.x] != 'D')
		data->sprite.y = data->sprite.next_y;
}

void	move_sprite(t_data *data)
{
	int	tmp;
	int	tmp_y;

	data->sprite.enemy_speed = 0.0035;
	data->sprite.buffer = 0.2;
	data->sprite.next_x = data->sprite.x;
	if (data->sprite.x < data->pos_x)
		data->sprite.next_x += data->sprite.enemy_speed;
	else
		data->sprite.next_x -= data->sprite.enemy_speed;
	if (data->sprite.next_x > data->sprite.x)
		tmp = (int)(data->sprite.next_x + data->sprite.buffer);
	else
		tmp = (int)(data->sprite.next_x - data->sprite.buffer);
	move_to_camera(data, &tmp, &tmp_y);
}
