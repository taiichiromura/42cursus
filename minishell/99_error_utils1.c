/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_error_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:27:46 by ktakeru           #+#    #+#             */
/*   Updated: 2025/08/26 14:03:41 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_lexer_error(t_token *head, char unexpected_char)
{
	ft_putstr_fd("bash: syntax error near unexpected character `", 2);
	ft_putchar_fd(unexpected_char, 2);
	ft_putendl_fd("'", 2);
	free_tokens(head);
	return (NULL);
}

void	pipe_error(void)
{
	perror("pipe failed");
	exit(1);
}

void	fork_error(void)
{
	perror("fork failed");
	exit(1);
}

int	fd_error(char *filename)
{
	ft_fprintf(STDERR_FILENO, "bash: ");
	perror(filename);
	return (1);
}

int	dup2_error(void)
{
	perror("dup2 failed");
	return (1);
}
