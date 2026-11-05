# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/17 12:45:16 by tmura             #+#    #+#              #
#    Updated: 2026/05/17 12:45:16 by tmura            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      = cub3D
LIBFT_DIR = ./include/libft
LIBFT     = $(LIBFT_DIR)/libft.a

MLX_DIR   = ./minilibx-linux
MLX_LIB   = $(MLX_DIR)/libmlx.a

CC        = cc
CFLAGS    = -Wall -Wextra -Werror -I ./include -I $(LIBFT_DIR) -I ./include/gnl -I $(MLX_DIR)
MLX       = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS      = src/main.c src/rendering.c src/map.c src/key_press.c src/utils.c \
            src/door.c src/set_texture_dir.c src/set_floor_ceiling.c src/move.c \
            src/set_position.c src/check_and_get_map.c src/check_map.c \
            src/set_camera_dir.c src/minimap.c src/render_sprites.c \
            src/describe_wall.c src/dda.c src/error_exit.c src/move_sprite.c \
            ./include/gnl/get_next_line.c ./include/gnl/get_next_line_utils.c

BONUS_SRCS = src_bonus/main_bonus.c src_bonus/rendering_bonus.c src_bonus/map_bonus.c \
            src_bonus/key_press_bonus.c src_bonus/utils_bonus.c src_bonus/door_bonus.c \
            src_bonus/set_texture_dir_bonus.c src_bonus/set_floor_ceiling_bonus.c \
            src_bonus/move_bonus.c src_bonus/set_position_bonus.c \
            src_bonus/check_and_get_map_bonus.c src_bonus/check_map_bonus.c \
            src_bonus/set_camera_dir_bonus.c src_bonus/minimap_bonus.c \
            src_bonus/render_sprites_bonus.c src_bonus/describe_wall_bonus.c \
            src_bonus/dda_bonus.c src_bonus/error_exit_bonus.c src_bonus/move_sprite_bonus.c \
            ./include/gnl/get_next_line.c ./include/gnl/get_next_line_utils.c

ifdef WITH_BONUS
    TARGET_OBJS = $(BONUS_SRCS:.c=.o)
else
    TARGET_OBJS = $(SRCS:.c=.o)
endif

all: $(NAME)

$(NAME): $(TARGET_OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(TARGET_OBJS) $(LIBFT) $(MLX) -o $(NAME)

bonus:
	@make WITH_BONUS=1 all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	rm -f $(SRCS:.c=.o) $(BONUS_SRCS:.c=.o)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
