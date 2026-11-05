/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:02:58 by tmura             #+#    #+#             */
/*   Updated: 2025/07/18 12:32:59 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

char	**copy_map(char **src, int height)
{
	char	**dst;
	int		i;

	dst = malloc(sizeof(char *) * (height + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < height)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			while (--i >= 0)
				free(dst[i]);
			free(dst);
			return (NULL);
		}
		i++;
	}
	dst[height] = NULL;
	return (dst);
}

int	is_valid_path(char **map, int h, int w)
{
	if (map[h][w] == '1' || map[h][w] == 'V')
		return (INVALID_PATH);
	if (map[h][w] == 'P')
		return (VALID_PATH);
	map[h][w] = 'V';
	return (is_valid_path(map, h + 1, w)
		|| is_valid_path(map, h - 1, w)
		|| is_valid_path(map, h, w + 1)
		|| is_valid_path(map, h, w - 1));
}

static int	check_paths(t_game *game)
{
	char	**dummy;
	int		h;
	int		w;

	h = -1;
	while (++h < game->map.height)
	{
		w = -1;
		while (++w < game->map.width)
		{
			if (game->map.data[h][w] == 'C'
				|| game->map.data[h][w] == 'E')
			{
				dummy = copy_map(game->map.data, game->map.height);
				if (!dummy)
					error_exit("Map copy failed");
				if (!is_valid_path(dummy, h, w))
					return (free_map(dummy), 0);
				free_map(dummy);
			}
		}
	}
	return (1);
}

int	is_valid_map(t_game *game)
{
	if (check_paths(game))
		return (VALID_MAP);
	free_all(game);
	error_exit("no valid path\n");
	return (INVALID_MAP);
}
