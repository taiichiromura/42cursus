# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/12 23:39:52 by tmura             #+#    #+#              #
#    Updated: 2025/07/18 13:38:59 by tmura            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       := so_long
BONUSNAME  := so_long_bonus

CC         := cc
CFLAGS     := -Wall -Wextra -Werror

LIBFTDIR   := libft
LIBFT      := $(LIBFTDIR)/libft.a
MLXDIR     := minilibx-linux
MLX        := $(MLXDIR)/libmlx.a

INCLUDES   := -Iinclude -I$(LIBFTDIR)/include -I$(MLXDIR)
MLXFLAGS   := -L$(MLXDIR) -lmlx -lXext -lX11 -lm
TMPDIR     := ar_tmp

MANDATORY_SRCS := \
	src/mandatory/main.c \
	src/mandatory/read_line_to_map.c \
	src/mandatory/is_valid_file.c \
	src/mandatory/is_rectangular.c \
	src/mandatory/close_game.c \
	src/mandatory/walls.c \
	src/mandatory/count_elements.c \
	src/mandatory/free.c \
	src/mandatory/errors.c \
	src/mandatory/utility.c \
	src/mandatory/load_images.c \
	src/mandatory/draw.c \
	src/mandatory/move_player.c \
	src/mandatory/move_enemy.c \
	src/mandatory/is_valid_map.c \
	src/mandatory/init_mlx.c \
	src/mandatory/update_frame.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c

BONUS_SRCS := \
	src/bonus/main.c \
	src/bonus/read_line_to_map.c \
	src/bonus/is_valid_file.c \
	src/bonus/is_rectangular.c \
	src/bonus/close_game.c \
	src/bonus/walls.c \
	src/bonus/count_elements.c \
	src/bonus/free.c \
	src/bonus/errors.c \
	src/bonus/utility.c \
	src/bonus/load_images.c \
	src/bonus/draw.c \
	src/bonus/move_player.c \
	src/bonus/move_enemy.c \
	src/bonus/is_valid_map.c \
	src/bonus/init_mlx.c \
	src/bonus/update_frame.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c

MANDATORY_OBJS := $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS     := $(BONUS_SRCS:.c=.o)

.PHONY: all bonus clean fclean re


all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(MANDATORY_OBJS)
	@mkdir -p $(TMPDIR)
	@cp $(LIBFT) $(TMPDIR)
	@cd $(TMPDIR) && ar x ../$(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(MANDATORY_OBJS) $(TMPDIR)/*.o -o $(NAME) $(MLXFLAGS)
	@rm -rf $(TMPDIR)


bonus: $(BONUSNAME)

$(BONUSNAME): $(LIBFT) $(MLX) $(BONUS_OBJS)
	@mkdir -p $(TMPDIR)
	@cp $(LIBFT) $(TMPDIR)
	@cd $(TMPDIR) && ar x ../$(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_OBJS) $(TMPDIR)/*.o -o $(BONUSNAME) $(MLXFLAGS)
	@rm -rf $(TMPDIR)


$(LIBFT):
	@$(MAKE) -s -C $(LIBFTDIR)

$(MLX):
	@$(MAKE) -s -C $(MLXDIR)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(MAKE) -C $(MLXDIR) clean
	@rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFTDIR) fclean
	@rm -f $(NAME) $(BONUSNAME)

re: fclean all
