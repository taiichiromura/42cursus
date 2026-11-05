/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:14:32 by tmura             #+#    #+#             */
/*   Updated: 2026/05/12 16:14:32 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_player_position(t_data *data)
{
	data->pos_x = data->pointer.w + 0.5;
	data->pos_y = data->pointer.h + 0.5;
	default_dir(data->map[data->pointer.h][data->pointer.w], data);
	data->map[data->pointer.h][data->pointer.w] = '0';
	data->pointer.cnt++;
}

void	set_sprite_position(t_data *data)
{
	data->sprite.x = data->pointer.w + 0.5;
	data->sprite.y = data->pointer.h + 0.5;
	data->sprite.exist = 1;
}

void	set_sprite_tex(char **paths)
{
	paths[5] = "textures/sprite1.xpm";
	paths[6] = "textures/sprite2.xpm";
	paths[7] = "textures/sprite3.xpm";
	paths[8] = "textures/sprite4.xpm";
	paths[9] = "textures/sprite5.xpm";
	paths[10] = "textures/sprite6.xpm";
	paths[11] = "textures/sprite7.xpm";
	paths[12] = "textures/sprite8.xpm";
	paths[13] = "textures/sprite9.xpm";
	paths[14] = "textures/sprite10.xpm";
}

void	free_stab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_stab_exit(t_data *data, char **map, int num, char *msg)
{
	free_stab(map);
	free_exit(data, num, msg);
}
