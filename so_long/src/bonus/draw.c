/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:30:13 by tmura             #+#    #+#             */
/*   Updated: 2025/07/18 12:31:10 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../../minilibx-linux/mlx.h"

void	dispay_count(const t_game *game)
{
	char	*count_str;
	char	*msg;
	char	*col_str;
	char	*msg2;

	count_str = ft_itoa(game->move_count);
	col_str = ft_itoa(game->elements.collectible_count);
	msg = ft_strjoin("Move Count: ", count_str);
	msg2 = ft_strjoin("Collectibles: ", col_str);
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, msg);
	mlx_string_put(game->mlx, game->win, 10, 30, 0xFFFF00, msg2);
	free(count_str);
	free(col_str);
	free(msg);
	free(msg2);
}

void	draw_map(const t_game *game)
{
	int		h;
	int		w;
	char	**map;

	map = game->map.data;
	h = 0;
	while (h < game->map.height)
	{
		w = 0;
		while (w < game->map.width)
		{
			draw_back_ground_tile(game, map[h][w], h, w);
			draw_fore_ground_tile(game, map[h][w], h, w);
			w++;
		}
		h++;
	}
	dispay_count(game);
}

void	draw_back_ground_tile(const t_game *game, const char tile,
			const int w, const int h)
{
	void	*img;

	img = NULL;
	if (tile == '1')
		img = game->img.wall;
	else
		img = game->img.floor;
	if (img)
		mlx_put_image_to_window(game->mlx, game->win, img,
			h * TILE_SIZE, w * TILE_SIZE);
}

void	draw_fore_ground_tile(const t_game *game, const char tile,
			const int w, const int h)
{
	void	*img;

	img = NULL;
	if (tile == 'P')
		img = game->img.player[game->anim_frame % 2];
	else if (tile == 'E')
	{
		if (!game->elements.collectible_count)
			img = game->img.exit;
		else
			img = game->img.fire;
	}
	else if (tile == 'C')
		img = game->img.collectible;
	else if (tile == 'X')
		img = game->img.enemy;
	if (img)
		mlx_put_image_to_window(game->mlx, game->win, img,
			h * TILE_SIZE, w * TILE_SIZE);
}
