/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:07:49 by tmura             #+#    #+#             */
/*   Updated: 2026/05/12 16:07:49 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	all_dir_texture_is_valid(t_data *data)
{
	int	cnt;

	cnt = 0;
	if (data->texture.no_path)
		cnt++;
	if (data->texture.so_path)
		cnt++;
	if (data->texture.we_path)
		cnt++;
	if (data->texture.ea_path)
		cnt++;
	if (data->fc_check[0] == 1)
		cnt++;
	if (data->fc_check[1] == 1)
		cnt++;
	return (cnt);
}

void	get_config_info(t_data *data)
{
	parse_config_line(data->map_info.line, data);
}

void	get_map_info(t_data *data)
{
	if (data->map_info.is_empty)
	{
		data->map_info.map_finished = FINISHED;
		return ;
	}
	if (data->map_info.map_finished == FINISHED)
	{
		free_exit(data, EMPTY_LINE, "empty line found in the map!\n");
	}
	data->map_info.tmp_width = ft_strlen(data->map_info.line);
	while (data->map_info.tmp_width > 0
		&& is_space_and_crlf(data->map_info.line[data->map_info.tmp_width - 1]))
	{
		data->map_info.line[data->map_info.tmp_width - 1] = '\0';
		data->map_info.tmp_width--;
	}
	if (data->map_width < data->map_info.tmp_width)
		data->map_width = data->map_info.tmp_width;
	if (!data->map_info.map_finished)
		data->map_height++;
}

void	get_info(t_data *data)
{
	data->map_info.line = get_next_line(data->fd);
	if (!data->map_info.line)
		free_exit(data, FAILED, "map empty!");
	while (data->map_info.line)
	{
		data->map_info.is_empty = is_empty_line(data->map_info.line);
		if (!data->map_info.in_map)
			get_config_info(data);
		if (data->map_info.in_map)
			get_map_info(data);
		free(data->map_info.line);
		data->map_info.line = NULL;
		data->file_rows++;
		data->map_info.line = get_next_line(data->fd);
	}
}
