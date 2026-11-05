# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 10:44:30 by tmura             #+#    #+#              #
#    Updated: 2025/06/01 12:09:43 by tmura            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCFILES = 	ft_printf.c \
		scan_line.c \
		print_strings.c \
		print_nums.c \
		output.c \
		base_convert.c \
		format.c \
		utils.c

CFLAGS = -Wall -Wextra -Werror $(addprefix -I,$(INCLUDES))
AR := ar
ARFLAGS := rcs
RM := rm -f
RMDIR := rm -rf

SRCDIR := src
OBJDIR := obj
INCDIR := include
LIBFTDIR := libft
TMPDIR := ar_tmp

SRCS := $(addprefix $(SRCDIR)/, $(SRCFILES))
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
INCLUDES := $(INCDIR) $(LIBFTDIR)/include

LIBFT := $(LIBFTDIR)/libft.a

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME): $(LIBFT) $(OBJS)
	mkdir -p $(TMPDIR)
	cp $(LIBFT) $(TMPDIR)
	cd $(TMPDIR) && $(AR) x ../$(LIBFT)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(TMPDIR)/*.o
	$(RMDIR) $(TMPDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	@$(RMDIR) $(OBJDIR)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re: fclean all

bonus: all

.PHONY:all clean fclean re bonus