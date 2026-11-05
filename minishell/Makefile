# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/13 16:55:05 by ktakeru           #+#    #+#              #
#    Updated: 2025/09/18 16:35:35 by ktakeru          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -lreadline -no-pie

SRCS = 01_main.c \
	01_main2.c \
       02_create_env_list.c \
       03_setup_signals.c \
       04_01_lexer.c\
       04_02_lexer_utils.c\
       05_01_validate_syntax.c\
       05_02_validate_syntax_utils.c\
       06_parser.c \
	06_append.c \
	06_parse_create_command.c \
	06_parse_create_command02.c \
	06_02_parse_first_command.c \
	06_01_parse_pipeline.c \
	06_parse_subshell.c \
       06_wildcard.c \
       07_expand_ast.c \
       07_expand_core.c \
       07_expand_core02.c \
       07_expand_core03.c \
       07_expand_word.c \
       07_expand_word_utils.c \
	07_quote_remove.c \
       07_quote_remove02.c \
       08_01_ast.c \
       08_02_ast_newlist1.c \
       08_02_ast_newlist2.c \
	09_01_execute_cmd.c \
       09_02_execute_cmd.c \
       09_03_execute_cmd.c \
       10_01_builtin.c \
       10_02_builtin_cd.c \
       10_03_builtin_export1.c \
       10_03_builtin_export2.c \
       10_04_builtin_unset.c \
       10_05_builtin_exit.c \
       10_06_builtin_echo.c \
       10_07_builtin_set_env.c \
       11_01_external_cmd.c \
       11_02_external_cmd_utils.c \
       11_02_external_cmd_utils2.c \
       11_03_env_management.c \
       12_01_pipeline.c \
       12_02_pipeline.c \
       13_subshell.c \
       14_01_redirect1.c \
       14_01_redirect2.c \
       14_02_redirect_heredoc1.c \
       14_02_redirect_heredoc2.c \
       14_02_redirect_heredoc3.c \
       14_02_redirect_heredoc4.c \
       50_ft_functions1.c \
	50_ft_functions2.c \
       98_free_utils1.c \
       98_free_utils2.c \
       99_error_utils1.c \
       99_error_utils2.c \

OBJS_DIR = .
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

LIBFT_DIR = libft
PRINTF_DIR = ft_printf

LIBFT_DIR = libft
PRINTF_DIR = ft_printf
LIBS = $(LIBFT_DIR)/libft.a $(PRINTF_DIR)/libftprintf.a
LIB_FLAGS = -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf

INCLUDES = -I. -I$(LIBFT_DIR) -I$(PRINTF_DIR)

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) $(LDFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBS):
	@echo "--- Making libraries ---"
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(PRINTF_DIR)

bonus: $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
