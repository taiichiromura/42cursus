/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 10:01:42 by t.mura            #+#    #+#             */
/*   Updated: 2026/05/17 21:36:30 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_E 101
# define K_LEFT 65361
# define K_RIGHT 65363
# define K_ESC 65307

# define PARSE_SUCCESS 0
# define PARSE_FAILED 1

# define EMPTY_LINE 3
# define IS_SPACE 1
# define IS_NOT_SPACE 0
# define LACK_OF_INFO 4
# define PATH_DUP 5
# define FAILED 6
# define IS_SPACE_OF_CRLF 1
# define FILENAME_WRONG 7

# define OK 0
# define ERROR -1
# define MAX_RGB 255
# define IS_TRUE 1
# define IS_FALSE -1
# define TRUE 0
# define FINISHED 1
# define NG 0

typedef struct s_dda
{
	double					camera_x;
	double					ray_dir_x;
	double					ray_dir_y;
	double					delta_dist_x;
	double					delta_dist_y;
	int						map_x;
	int						map_y;
	double					side_dist_x;
	double					side_dist_y;
	int						step_x;
	int						step_y;
	int						side;
	int						hit;
	double					perp_wall_dist;
	int						line_height;
	int						draw_start;
	int						draw_end;
	int						tex_num;
	double					wall_x;
	int						tex_x;
	int						tex_y;
	double					step;
	double					tex_pos;
}	t_dda;

typedef struct s_img
{
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
	int						width;
	int						height;
}	t_img;

typedef struct s_flg
{
	int						key_w;
	int						key_s;
	int						key_a;
	int						key_d;
	int						key_left;
	int						key_right;
	int						key_esc;
}	t_flg;

typedef struct s_texture
{
	char					*no_path;
	char					*so_path;
	char					*we_path;
	char					*ea_path;
	int						floor_color;
	int						ceiling_color;
}	t_texture;

typedef struct s_sprite
{
	double					x;
	double					y;
	int						tex_id;
	int						exist;
	double					enemy_speed;
	double					buffer;
	double					next_x;
	double					next_y;
	double					spr_x;
	double					spr_y;
	double					inv_det;
	double					transform_x;
	double					transform_y;
	int						spr_screen_x;
	int						spr_height;
	int						spr_width;
	int						draw_start_y;
	int						draw_end_y;
	int						draw_start_x;
	int						draw_end_x;
	int						tex_x;
	int						d;
	int						tex_y;
	int						color;
	int						current_frame;
	int						frame_counter;
}	t_sprite;

typedef struct s_map_info
{
	char					*line;
	int						in_map;
	int						parse_result;
	int						tmp;
	int						is_empty;
	int						map_finished;
	int						tmp_width;

}	t_map_info;

typedef struct s_pointer
{
	int						h;
	int						w;
	int						cnt;
}	t_pointer;

typedef struct s_minimap
{
	int						size;
	int						color;
	int						x;
	int						y;
}	t_minimap;

typedef struct s_cub3d
{
	char					*filename;
	void					*mlx;
	void					*win;
	void					*img;
	void					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
	char					**map;
	char					**cmap;
	char					**copy_map;
	int						map_height;
	int						map_width;
	double					pos_x;
	double					pos_y;
	double					dir_x;
	double					dir_y;
	double					plane_x;
	double					plane_y;
	double					dx;
	double					dy;
	t_flg					flg;
	t_texture				texture;
	t_img					tex[15];
	int						w;
	int						h;
	int						fc_check[2];
	double					z_buffer[SCREEN_WIDTH];
	t_sprite				sprite;
	t_dda					dda;
	t_map_info				map_info;
	int						fd;
	int						file_rows;
	int						i;
	int						idx;
	char					*trimmed;
	t_pointer				pointer;
	t_minimap				minimap;
}	t_data;

int							render_frame(t_data *data);
int							key_press(int keycode, t_data *data);
int							key_release(int keycode, t_data *data);
int							move(t_data *data);
int							main_loop(t_data *data);
int							initialization(t_data *data);
int							map_init(t_data *data);
void						copy_line(char *dst, char *tmp, t_data *data);
void						make_map(int fd, t_data *data);
char						**copy_map(t_data *data);
void						default_dir(char orientation, t_data *data);
int							check_characters(t_data *data);
void						check_wall(t_data *data, char **map, int h, int w);
void						free_stab(char **tab);
int							parse_rgb(char *str);
void						load_textures(t_data *data);
int							parse_config_line(char *line, t_data *data);
void						my_mlx_pixel_put(t_data *data,
								int x, int y, int color);
int							mouse_move(int x, int y, t_data *data);
unsigned int				get_pixel_color(t_img *img, int x, int y);
void						move_sprite(t_data *data);
void						check_death(t_data *data);
void						dda(t_data *data);
void						free_exit(t_data *data,
								int status, char *error_msg);
void						free_map(t_data *data);
int							ft_is_space(char *character);
int							is_space(char c);
void						check_and_get_map_info(t_data *data);
void						free_textures(t_data *data);
int							is_config_info(t_data *data);
void						copy_line_to_map(t_data *data);
void						draw_square(t_data *data, int x, int y, int color);
void						open_close_door(t_data *data);
int							parse_rgb(char *str);
void						set_north_path(t_data *data, char *trimmed);
void						set_south_path(t_data *data, char *trimmed);
void						set_west_path(t_data *data, char *trimmed);
void						set_east_path(t_data *data, char *trimmed);
void						set_floor_color(t_data *data, char *trimmed);
void						set_ceiling_color(t_data *data, char *trimmed);
void						calc_move_amount(t_data *data);
void						check_wall_exit(t_data *data);
void						rotate(t_data *data);
int							close_window(t_data *data);
int							all_dir_texture_is_valid(t_data *data);
void						get_config_info(t_data *data);
void						get_info(t_data *data);
void						check_wall(t_data *data, char **map, int h, int w);
int							check_character_and_wall(t_data *data);
void						free_stab(char **tab);
int							is_empty_line(char *line);
void						set_player_position(t_data *data);
void						set_sprite_position(t_data *data);
void						default_dir(char orientation, t_data *data);
void						set_orientation_north(t_data *data);
void						set_orientation_south(t_data *data);
void						set_orientation_west(t_data *data);
void						set_orientation_east(t_data *data);
void						draw_minimap(t_data *data);
void						draw_point(t_data *data, int x, int y, int color);
void						draw_square(t_data *data, int x, int y, int color);
void						render_sprites(t_data *data);
void						draw_sprite(t_data *data);
void						put_sprite_pixel(t_data *data, int x);
void						calc_sprite_projection(t_data *data);
void						move_sprite(t_data *data);
void						put_sail_floor(t_data *data);
void						describe_wall1(t_data *data);
void						describe_wall2(t_data *data);
void						describe_wall3(t_data *data);
void						describe_wall4(t_data *data, const int x);
void						set_dir(t_data *data, const int x);
void						dda(t_data *data);
void						calc_dist_to_wall(t_data *data);
void						load_textures(t_data *data);
void						check_death(t_data *data);
int							is_empty_line(char *line);
int							is_space(char c);
int							is_space_and_crlf(char c);
int							ft_is_space(char *str);
void						type_of_content(t_data *data);
void						free_fail(t_data *data);
void						move_to_camera(t_data *data, int *tmp, int *tmp_y);
void						set_start_to_end(t_data *data);
int							in_map(t_data *data);
void						update_sprite_animation(t_data *data);
void						set_sprite_tex(char **paths);
void						free_stab_exit(t_data *data, char **map,
								int num, char *msg);

#endif
