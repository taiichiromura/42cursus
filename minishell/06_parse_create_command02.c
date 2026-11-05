/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_parse_create_command02.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:59:18 by tmura             #+#    #+#             */
/*   Updated: 2025/08/27 12:00:08 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_word_token(
	t_command *cmd, t_token **cur, int *argc, int *cap)
{
	if (!append_any(cmd, (*cur)->value, argc, cap))
		return (-1);
	*cur = (*cur)->next;
	return (1);
}

int	handle_redirection_token(
	t_command *cmd, t_token **cur)
{
	t_token	*file;

	file = (*cur)->next;
	if (!file || file->type != T_WORD)
	{
		ft_fprintf(STDERR_FILENO,
			"bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	add_redirect(cmd,
		(t_redirect_type)((*cur)->type - T_REDIR_IN), file->value);
	*cur = file->next;
	return (2);
}

int	parse_tokens_into_cmd(
	t_command *cmd, t_token **cur, int *argc, int *cap)
{
	int	count;
	int	rc;

	count = 0;
	while (*cur)
	{
		if ((*cur)->type == T_WORD)
			rc = handle_word_token(cmd, cur, argc, cap);
		else if (is_redir_token((*cur)->type))
			rc = handle_redirection_token(cmd, cur);
		else
			break ;
		if (rc < 0)
			return (-1);
		count += rc;
	}
	return (count);
}
