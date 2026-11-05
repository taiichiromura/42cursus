/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:01:49 by tmura             #+#    #+#             */
/*   Updated: 2026/05/16 17:01:49 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	set_start_to_end(t_data *data)
{
	data->sprite.draw_start_y
		= -data->sprite.spr_height / 2 + SCREEN_HEIGHT / 2;
	if (data->sprite.draw_start_y < 0)
		data->sprite.draw_start_y = 0;
	data->sprite.draw_end_y = data->sprite.spr_height / 2
		+ SCREEN_HEIGHT / 2;
	if (data->sprite.draw_end_y >= SCREEN_HEIGHT)
		data->sprite.draw_end_y = SCREEN_HEIGHT - 1;
	data->sprite.draw_start_x = -data->sprite.spr_width
		/ 2 + data->sprite.spr_screen_x;
	if (data->sprite.draw_start_x < 0)
		data->sprite.draw_start_x = 0;
	data->sprite.draw_end_x = data->sprite.spr_width
		/ 2 + data->sprite.spr_screen_x;
	if (data->sprite.draw_end_x >= SCREEN_WIDTH)
		data->sprite.draw_end_x = SCREEN_WIDTH - 1;
}

void	calc_sprite_projection(t_data *data)
{
	data->sprite.spr_x = data->sprite.x - data->pos_x;
	data->sprite.spr_y = data->sprite.y - data->pos_y;
	data->sprite.inv_det = 1.0
		/ (data->plane_x * data->dir_y - data->dir_x * data->plane_y);
	data->sprite.transform_x = data->sprite.inv_det * (data->dir_y
			* data->sprite.spr_x - data->dir_x * data->sprite.spr_y);
	data->sprite.transform_y = data->sprite.inv_det
		* (-data->plane_y * data->sprite.spr_x
			+ data->plane_x * data->sprite.spr_y);
	data->sprite.spr_screen_x = (int)((SCREEN_WIDTH / 2)
			* (1 + data->sprite.transform_x / data->sprite.transform_y));
	data->sprite.spr_height
		= abs((int)(SCREEN_HEIGHT / data->sprite.transform_y));
	data->sprite.spr_width
		= abs((int)(SCREEN_HEIGHT / data->sprite.transform_y));
	set_start_to_end(data);
}

void	put_sprite_pixel(t_data *data, int x)
{
	int		y;

	y = data->sprite.draw_start_y;
	while (y < data->sprite.draw_end_y)
	{
		data->sprite.d = y * 256 - SCREEN_HEIGHT
			* 128 + data->sprite.spr_height * 128;
		data->sprite.tex_y = ((data->sprite.d * 64)
				/ data->sprite.spr_height) / 256;
		data->sprite.color = get_pixel_color(
				&data->tex[5 + data->sprite.current_frame],
				data->sprite.tex_x, data->sprite.tex_y);
		if ((data->sprite.color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(data, x, y, data->sprite.color);
		y++;
	}
}

void	draw_sprite(t_data *data)
{
	int		x;

	x = data->sprite.draw_start_x;
	while (x < data->sprite.draw_end_x)
	{
		data->sprite.tex_x = (int)(256 * (x - (-data->sprite.spr_width
						/ 2 + data->sprite.spr_screen_x))
				* 64 / data->sprite.spr_width) / 256;
		if (data->sprite.transform_y > 0
			&& data->sprite.transform_y < data->z_buffer[x])
			put_sprite_pixel(data, x);
		x++;
	}
}

void	render_sprites(t_data *data)
{
	calc_sprite_projection(data);
	draw_sprite(data);
}
