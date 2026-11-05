# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 00:00:00 by tmura             #+#    #+#              #
#    Updated: 2025/07/12 12:20:54 by tmura            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
BONUS = checker
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include

LIBFTDIR  := libft
LIBFT     := $(LIBFTDIR)/libft.a

PUSH_SWAP_SRC = ./src/mandatory/push_swap.c ./src/mandatory/push.c \
				./src/mandatory/rotate_tail_head.c ./src/mandatory/rotate_head_tail.c \
                ./src/mandatory/lis_process.c ./src/mandatory/mark_lis_nodes.c \
				./src/mandatory/push_unmarked_nodes.c ./src/mandatory/calculate.c \
                ./src/mandatory/swap.c ./src/mandatory/errors.c ./src/mandatory/sort_a.c ./src/mandatory/utils.c \
				./src/mandatory/min_max.c ./src/mandatory/find_position.c \
 	            ./src/mandatory/back_to_a.c ./src/mandatory/safe_atoi.c \
				./src/mandatory/node_ctl.c ./src/mandatory/exec_pattern.c

BONUS_ONLY_SRC = ./src/bonus/main.c ./src/bonus/checker.c ./src/bonus/push_bonus.c\
				 ./src/bonus/rotate_tail_head_bonus.c ./src/bonus/rotate_head_tail_bonus.c \
                 ./src/bonus/swap_bonus.c ./src/bonus/errors_bonus.c \
				 ./src/bonus/utils_bonus.c ./src/bonus/safe_atoi_bonus.c \
				 ./src/bonus/node_ctl_bonus.c

SRC = $(PUSH_SWAP_SRC)
BONUS_SRC = $(BONUS_ONLY_SRC)


OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(BONUS)

$(BONUS): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(BONUS)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
