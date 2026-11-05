/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:25:51 by tmura             #+#    #+#             */
/*   Updated: 2025/07/18 13:35:06 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	check_top_wall(char **map, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1')
		{
			free_map(map);
			error_exit("top wall is not closed\n");
		}
		i++;
	}
}

void	check_left_walls(char **map, int height)
{
	int	i;

	i = 1;
	while (i < height - 1)
	{
		if (map[i][0] != '1')
		{
			free_map(map);
			error_exit("left wall is not closed\n");
		}
		i++;
	}
}

void	check_right_walls(char **map, int width, int height)
{
	int	i;

	i = 1;
	while (i < height - 1)
	{
		if (map[i][width - 1] != '1')
		{
			free_map(map);
			error_exit("right wall is not closed\n");
		}
		i++;
	}
}

void	check_bottom_wall(char **map, int width, int height)
{
	int	i;

	i = 0;
	while (i < width)
	{
		if (map[height - 1][i] != '1')
		{
			free_map(map);
			error_exit("bottom wall is not closed\n");
		}
		i++;
	}
}

void	check_wall(const t_game *game)
{
	char	**map;
	int		width;
	int		height;

	map = game->map.data;
	width = game->map.width;
	height = game->map.height;
	check_top_wall(map, width);
	check_bottom_wall(map, width, height);
	check_left_walls(map, height);
	check_right_walls(map, width, height);
}
