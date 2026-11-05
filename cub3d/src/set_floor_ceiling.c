/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_floor_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:23:40 by tmura             #+#    #+#             */
/*   Updated: 2026/05/12 14:23:40 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_sail_floor(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < SCREEN_HEIGHT)
		{
			if (j < SCREEN_HEIGHT / 2)
				my_mlx_pixel_put(data, i, j, data->texture.ceiling_color);
			else
				my_mlx_pixel_put(data, i, j, data->texture.floor_color);
			j++;
		}
		i++;
	}
}

void	set_floor_color(t_data *data, char *trimmed)
{
	if (data->fc_check[0] == 1)
		free_exit(data, PATH_DUP, "FLOOR");
	data->texture.floor_color = parse_rgb(trimmed + 2);
	if (data->texture.floor_color == -1)
		free_exit(data, FAILED, data->map_info.line);
	data->fc_check[0] = 1;
}

void	set_ceiling_color(t_data *data, char *trimmed)
{
	if (data->fc_check[1] == 1)
		free_exit(data, PATH_DUP, "CEILING");
	data->texture.ceiling_color = parse_rgb(trimmed + 2);
	if (data->texture.ceiling_color == -1)
		free_exit(data, PARSE_FAILED, data->map_info.line);
	data->fc_check[1] = 1;
}
