/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:22:37 by tmura             #+#    #+#             */
/*   Updated: 2025/07/18 12:24:22 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../../minilibx-linux/mlx.h"

int	action(char next, t_game *game, t_move *move)
{
	if (next == '1')
		return (0);
	if (next == 'X')
	{
		error("GAME OVER\n");
		game->map.data[move->new_h][move->new_w] = '0';
		close_game(game);
	}
	if (next == 'C')
	{
		game->elements.collectible_count--;
		game->map.data[move->new_h][move->new_w] = '0';
	}
	if (next == 'E')
	{
		if (game->elements.collectible_count == 0)
		{
			error("CLEAR!\n");
			close_game(game);
		}
		return (0);
	}
	return (1);
}

void	move_forward(t_game *game, t_move *move)
{
	game->map.data[move->old_h][move->old_w] = '0';
	game->elements.player_h = move->new_h;
	game->elements.player_w = move->new_w;
	game->map.data[move->new_h][move->new_w] = 'P';
	game->move_count++;
	draw_map(game);
}

void	move_player(t_game *game, int dh, int dw)
{
	t_move	move;
	char	next;

	move = (t_move){0};
	move.old_h = game->elements.player_h;
	move.old_w = game->elements.player_w;
	move.new_h = move.old_h + dh;
	move.new_w = move.old_w + dw;
	next = game->map.data[move.new_h][move.new_w];
	if (action(next, game, &move))
		move_forward(game, &move);
}
