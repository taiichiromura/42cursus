/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:42:10 by tmura             #+#    #+#             */
/*   Updated: 2026/05/12 14:42:10 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	default_dir(char orientation, t_data *data)
{
	if (orientation == 'N')
		set_orientation_north(data);
	else if (orientation == 'S')
		set_orientation_south(data);
	else if (orientation == 'W')
		set_orientation_west(data);
	else if (orientation == 'E')
		set_orientation_east(data);
}

void	set_orientation_north(t_data *data)
{
	data->dir_x = 0;
	data->dir_y = -1;
	data->plane_x = 0.66;
	data->plane_y = 0;
}

void	set_orientation_south(t_data *data)
{
	data->dir_x = 0;
	data->dir_y = 1;
	data->plane_x = -0.66;
	data->plane_y = 0;
}

void	set_orientation_west(t_data *data)
{
	data->dir_x = -1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = -0.66;
}

void	set_orientation_east(t_data *data)
{
	data->dir_x = 1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = 0.66;
}
