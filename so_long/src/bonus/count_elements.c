/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:29:00 by tmura             #+#    #+#             */
/*   Updated: 2025/07/18 12:29:01 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	tile_type(const char tile, t_game *game, int h, int w)
{
	if (tile == 'P')
	{
		game->elements.player_count++;
		game->elements.player_h = h;
		game->elements.player_w = w;
	}
	else if (tile == 'E')
		game->elements.exit_count++;
	else if (tile == 'C')
		game->elements.collectible_count++;
	else if (tile == 'X')
	{
		game->enemy.h = h;
		game->enemy.w = w;
		game->enemy.dir = 1;
		game->enemy.count++;
	}
	else if (tile != '0' && tile != '1')
	{
		free_all(game);
		error_exit("Invalid character in map");
	}
}

void	count_elements(t_game *game)
{
	char	tile;
	int		h;
	int		w;

	h = 0;
	while (h < game->map.height)
	{
		w = 0;
		while (w < game->map.width)
		{
			tile = game->map.data[h][w];
			tile_type(tile, game, h, w);
			w++;
		}
		h++;
	}
}

void	check_elements(t_game *game)
{
	count_elements(game);
	if (game->elements.player_count != 1)
	{
		free_all(game);
		error_exit("map must contain exactly 1 player\n");
	}
	if (game->elements.exit_count < 1)
	{
		free_all(game);
		error_exit("map must contain at least 1 exit\n");
	}
	if (game->elements.collectible_count < 1)
	{
		free_all(game);
		error_exit("map must contain at least 1 collectible\n");
	}
	if (game->enemy.count > 1)
	{
		free_all(game);
		error_exit("map must contain at least 1 collectible\n");
	}
}
