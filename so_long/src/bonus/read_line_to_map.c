/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_to_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:57:15 by tmura             #+#    #+#             */
/*   Updated: 2025/07/18 12:01:31 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

char	*line_to_lines(const int fd, int *is_contain_only_new_line)
{
	char	*line;
	char	*lines;
	char	*attached;

	line = NULL;
	lines = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n')
			*is_contain_only_new_line = 1;
		attached = ft_strjoin(lines, line);
		free(lines);
		lines = attached;
		free(line);
	}
	return (lines);
}

void	is_valid_line(char *lines, int is_contain_only_new_line)
{
	if (!lines)
		error_exit("read map lines failed\n");
	if (!lines || lines[0] == '\0')
	{
		free(lines);
		error_exit("map is empty.\n");
	}
	if (is_contain_only_new_line)
	{
		free(lines);
		error_exit("map contain only new line\n");
	}
}

void	read_line_to_map(t_game *game, char *filename)
{
	int		fd;
	char	*lines;
	int		is_contain_only_new_line;

	is_contain_only_new_line = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit("open failed\n");
	lines = line_to_lines(fd, &is_contain_only_new_line);
	close(fd);
	is_valid_line(lines, is_contain_only_new_line);
	game->map.data = ft_split(lines, '\n');
	free(lines);
	if (!game->map.data)
		error_exit("split failed\n");
	game->map.height = 0;
	while (game->map.data[game->map.height])
		game->map.height++;
	game->map.width = ft_strlen(game->map.data[0]);
	if (game->map.width == 0 || game->map.height == 0)
		error_exit("invalid map size\n");
}
