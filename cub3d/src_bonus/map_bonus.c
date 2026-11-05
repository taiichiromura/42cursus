/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:02:28 by tmura             #+#    #+#             */
/*   Updated: 2026/05/16 17:02:28 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

char	**copy_map(t_data *data)
{
	int	i;

	data->copy_map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->copy_map)
		free_exit(data, 6, "malloc failed!");
	i = 0;
	while (i < data->map_height)
	{
		data->copy_map[i] = ft_strdup(data->map[i]);
		if (!data->copy_map[i])
		{
			free_stab(data->copy_map);
			free_exit(data, 6, "ft_strdup failed!");
		}
		i++;
	}
	data->copy_map[i] = NULL;
	return (data->copy_map);
}

int	in_config(t_data *data)
{
	if (data->i < data->file_rows - data->map_height)
	{
		data->i++;
		free(data->map_info.line);
		return (1);
	}
	return (0);
}

void	make_map(int fd, t_data *data)
{
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return ;
	while (1)
	{
		data->map_info.line = get_next_line(fd);
		if (!data->map_info.line)
			break ;
		if (in_config(data))
			continue ;
		if (data->i < data->file_rows)
		{
			data->map[data->idx] = malloc(sizeof(char) * (data->map_width + 1));
			if (!data->map[data->idx])
				free_exit(data, FAILED, "malloc failed!");
			ft_strlcpy(data->map[data->idx],
				data->map_info.line, data->map_width + 1);
			data->idx++;
		}
		free(data->map_info.line);
	}
	data->map[data->idx] = NULL;
}

int	map_init(t_data *data)
{
	data->fd = open(data->filename, O_RDONLY);
	if (data->fd < 0)
	{
		perror("Failed to open file");
		return (1);
	}
	get_info(data);
	if (all_dir_texture_is_valid(data) != 6)
		free_exit(data, FAILED, "lack of info");
	if (data->map_info.tmp == 2)
		free_exit(data, 1, "config error\n");
	close(data->fd);
	data->fd = open(data->filename, O_RDONLY);
	if (data->fd < 0)
		return (1);
	make_map(data->fd, data);
	check_character_and_wall(data);
	close(data->fd);
	return (0);
}
