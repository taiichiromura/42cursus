/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_dir_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:01:01 by tmura             #+#    #+#             */
/*   Updated: 2026/05/16 17:01:01 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	load_textures(t_data *data)
{
	char	*paths[15];
	int		i;

	i = 0;
	paths[0] = data->texture.no_path;
	paths[1] = data->texture.so_path;
	paths[2] = data->texture.we_path;
	paths[3] = data->texture.ea_path;
	paths[4] = "textures/door.xpm";
	set_sprite_tex(paths);
	while (i < 15)
	{
		data->fd = open(paths[i], O_RDONLY);
		if (data->fd < 0)
			free_exit(data, FAILED, "Texture file not found or inaccessible");
		close(data->fd);
		data->tex[i].img = mlx_xpm_file_to_image(data->mlx,
				paths[i], &data->w, &data->h);
		if (!data->tex[i].img)
			free_exit(data, FAILED, "invalid file path");
		data->tex[i].addr = mlx_get_data_addr(data->tex[i].img,
				&data->tex[i].bits_per_pixel, &data->tex[i].line_length,
				&data->tex[i].endian);
		i++;
	}
}

void	set_north_path(t_data *data, char *trimmed)
{
	if (data->texture.no_path)
		free_exit(data, PATH_DUP, data->texture.no_path);
	data->texture.no_path = ft_strtrim(trimmed + 3, " \f\n\r\t\v");
}

void	set_south_path(t_data *data, char *trimmed)
{
	if (data->texture.so_path)
		free_exit(data, PATH_DUP, data->texture.so_path);
	data->texture.so_path = ft_strtrim(trimmed + 3, " \f\n\r\t\v");
}

void	set_west_path(t_data *data, char *trimmed)
{
	if (data->texture.we_path)
		free_exit(data, PATH_DUP, data->texture.we_path);
	data->texture.we_path = ft_strtrim(trimmed + 3, " \f\n\r\t\v");
}

void	set_east_path(t_data *data, char *trimmed)
{
	if (data->texture.ea_path)
		free_exit(data, PATH_DUP, data->texture.ea_path);
	data->texture.ea_path = ft_strtrim(trimmed + 3, " \f\n\r\t\v");
}
