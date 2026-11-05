/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:25:25 by tmura             #+#    #+#             */
/*   Updated: 2025/07/18 12:38:41 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	move_enemy(t_enemy *enemy, t_game *game)
{
	int	h;
	int	next_w;

	h = enemy->h;
	next_w = enemy->w + enemy->dir;
	if (!(game->map.data[h][next_w] == '0' || game->map.data[h][next_w] == 'P'))
	{
		enemy->dir *= -1;
		return ;
	}
	if (game->elements.player_h == h && game->elements.player_w == next_w)
	{
		error("GAME OVER\n");
		close_game(game);
	}
	game->map.data[h][enemy->w] = '0';
	game->map.data[h][next_w] = 'X';
	enemy->w = next_w;
}
