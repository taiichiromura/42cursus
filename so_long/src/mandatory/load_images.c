/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:08:24 by tmura             #+#    #+#             */
/*   Updated: 2025/07/18 12:32:08 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../../minilibx-linux/mlx.h"

static void	load_image_named(void *mlx, void **img,
	char *path, char *err_msg)
{
	int	width;
	int	height;

	*img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!(*img))
		error_exit(err_msg);
}

void	load_images(t_game *game)
{
	load_image_named(game->mlx, (void **)&game->img.wall,
		"img/wall.xpm", "Failed to load wall.xpm");
	load_image_named(game->mlx, (void **)&game->img.floor,
		"img/floor.xpm", "Failed to load floor.xpm");
	load_image_named(game->mlx, (void **)&game->img.player[0],
		"img/player1.xpm", "Failed to load player1.xpm");
	load_image_named(game->mlx, (void **)&game->img.player[1],
		"img/player2.xpm", "Failed to load player2.xpm");
	load_image_named(game->mlx, (void **)&game->img.fire,
		"img/fire.xpm", "Failed to load fire.xpm");
	load_image_named(game->mlx, (void **)&game->img.exit,
		"img/exit.xpm", "Failed to load exit.xpm");
	load_image_named(game->mlx, (void **)&game->img.collectible,
		"img/collectible.xpm", "Failed to load collectible.xpm");
	load_image_named(game->mlx, (void **)&game->img.enemy,
		"img/ganon_sit.xpm", "Failed to load ganon_sit.xpm");
}
