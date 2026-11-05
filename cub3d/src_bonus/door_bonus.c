/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:02:56 by tmura             #+#    #+#             */
/*   Updated: 2026/05/16 17:02:56 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	open_close_door(t_data *data)
{
	int	target_x;
	int	target_y;

	target_x = (int)(data->pos_x + data->dir_x * 1.2);
	target_y = (int)(data->pos_y + data->dir_y * 1.2);
	if (target_x < 0 || target_x >= data->map_width
		|| target_y < 0 || target_y >= data->map_height)
		return ;
	if (data->map[target_y][target_x] == 'D')
	{
		data->map[target_y][target_x] = 'O';
	}
	else if (data->map[target_y][target_x] == 'O')
	{
		if ((int) data->pos_y != target_x || (int) data->pos_y != target_y)
			data->map[target_y][target_x] = 'D';
	}
}
