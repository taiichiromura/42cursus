/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_rectangular.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:02:50 by tmura             #+#    #+#             */
/*   Updated: 2025/07/18 12:02:52 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	check_shape(const t_game *game)
{
	int	i;
	int	line_length;
	int	expected_width;

	expected_width = ft_strlen(game->map.data[0]);
	i = 1;
	while (game->map.data[i])
	{
		line_length = ft_strlen(game->map.data[i]);
		if (line_length != expected_width)
		{
			free_all(game);
			error_exit("map is not rectangular\n");
		}
		i++;
	}
}
