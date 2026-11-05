# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 21:43:13 by tmura             #+#    #+#              #
#    Updated: 2025/07/24 14:53:50 by tmura            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      := pipex

CC        := cc
CFLAGS    := -Wall -Wextra -Werror

LIBFTDIR  := libft
LIBFT     := $(LIBFTDIR)/libft.a

TMPDIR    := ar_tmp

MANDATORY_SRCS := \
	src/pipex.c \
	src/utils.c \
	src/error_massages.c \
	src/process_exec.c \
	src/safe_call_bonus.c

BONUS_SRCS := \
	src/pipex_bonus.c \
	src/utils_bonus.c \
	src/error_massages_bonus.c \
	src/here_doc.c \
	src/here_doc_expand.c \
	src/process_exec_bonus.c \
	src/safe_call_bonus.c

MANDATORY_OBJS := $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS     := $(BONUS_SRCS:.c=.o)

ifdef BONUS
OBJS := $(BONUS_OBJS)
else
OBJS := $(MANDATORY_OBJS)
endif

INCLUDES  := -Iinclude -I$(LIBFTDIR)/include

.PHONY: all bonus clean fclean re FORCE

all: $(NAME)

bonus:
	@$(MAKE) --no-print-directory BONUS=1 all

$(NAME): $(LIBFT) $(OBJS)
	@$(MAKE) -C $(LIBFTDIR)
	@mkdir -p $(TMPDIR)
	@cp $(LIBFT) $(TMPDIR)
	@cd $(TMPDIR) && ar x ../$(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(TMPDIR)/*.o -o $(NAME)
	@rm -rf $(TMPDIR)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFTDIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all
