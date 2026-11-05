/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:02:36 by tmura             #+#    #+#             */
/*   Updated: 2026/05/16 17:02:36 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	handle_expose(void *param)
{
	t_data	*data;

	data = (t_data *) param;
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	main_loop(t_data *data)
{
	move(data);
	check_death(data);
	move_sprite(data);
	render_frame(data);
	update_sprite_animation(data);
	return (0);
}

int	initialization(t_data *data)
{
	map_init(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	return (0);
}

void	check_map_file(t_data *data, char *filename)
{
	int	size;

	data->fd = -1;
	size = ft_strlen(filename);
	if (size < 5 || ft_strncmp(&filename[size - 4], ".cub", 4) != 0)
		free_exit(data, FILENAME_WRONG, filename);
	data->fd = open(filename, O_RDONLY);
	if (data->fd < 0)
		free_exit(data, FILENAME_WRONG, "Could not open file");
	close(data->fd);
	data->filename = filename;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		write(2, "Error\nUsage wrong!\n", 19);
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	check_map_file(&data, argv[1]);
	initialization(&data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win, 6, (1L << 6), mouse_move, &data);
	mlx_expose_hook(data.win, handle_expose, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	load_textures(&data);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_loop(data.mlx);
	free_exit(&data, 0, "propery game stoped");
	return (0);
}
