/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:02:50 by tmura             #+#    #+#             */
/*   Updated: 2026/05/16 17:02:50 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	put_config_error(t_data *data, int status, char *error_msg)
{
	(void)data;
	if (status == PARSE_FAILED)
	{
		write(2, "Error\n", 6);
		write(2, error_msg, ft_strlen(error_msg));
		write(2, "is not proper usage!\n", 21);
	}
	if (status == EMPTY_LINE)
	{
		write(2, "Error\n", 6);
		write(2, error_msg, ft_strlen(error_msg));
	}
	if (status == FILENAME_WRONG)
	{
		write(2, "Error\n", 6);
		write(2, "filename format wrong!\n", 23);
		write(2, error_msg, ft_strlen(error_msg));
		write(2, "\n", 1);
	}
	if (status == PATH_DUP)
	{
		write(2, "Error\npath:", 11);
		write(2, error_msg, ft_strlen(error_msg));
		write(2, "\nalready set!\n", 14);
	}
}

void	free_fail(t_data *data)
{
	char	*tmp;

	if (data->texture.no_path)
		free(data->texture.no_path);
	if (data->texture.so_path)
		free(data->texture.so_path);
	if (data->texture.we_path)
		free(data->texture.we_path);
	if (data->texture.ea_path)
		free(data->texture.ea_path);
	if (data->map)
		free_map(data);
	if (data->map_info.line)
	{
		free(data->map_info.line);
		data->map_info.line = NULL;
	}
	tmp = get_next_line(data->fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(data->fd);
	}
}

void	free_mlx(t_data *data, int status, char *error_msg)
{
	int	i;

	if (status == 0)
	{
		write(2, error_msg, ft_strlen(error_msg));
		write(2, "\n", 1);
	}
	i = 0;
	while (i < 6)
	{
		if (data->tex[i].img)
			mlx_destroy_image(data->mlx, data->tex[i].img);
		i++;
	}
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

void	free_exit(t_data *data, int status, char *error_msg)
{
	if (status == FAILED)
	{
		write(2, "Error\n", 6);
		write(2, error_msg, ft_strlen(error_msg));
		write(2, "\n", 1);
	}
	put_config_error(data, status, error_msg);
	free_fail(data);
	free_mlx(data, status, error_msg);
	exit(status);
}

int	close_window(t_data *data)
{
	free_exit(data, 0, "user closed window");
	exit(0);
	return (0);
}
