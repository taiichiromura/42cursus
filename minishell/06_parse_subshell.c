/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_parse_subshell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:51:05 by tmura             #+#    #+#             */
/*   Updated: 2025/08/27 16:53:43 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(int t)
{
	if (t == T_REDIR_IN || t == T_REDIR_OUT)
		return (1);
	if (t == T_REDIR_APPEND || t == T_REDIR_HEREDOC)
		return (1);
	return (0);
}

int	parse_redirections(t_command *cmd, t_token **cursor)
{
	t_token	*cur;
	t_token	*filename;
	int		rtype;

	cur = *cursor;
	while (cur && is_redir_token(cur->type))
	{
		filename = cur->next;
		if (!filename || filename->type != T_WORD)
		{
			ft_fprintf(STDERR_FILENO, "Syntax error: expected filename "
				"after redirection\n");
			return (0);
		}
		rtype = (int)(cur->type - T_REDIR_IN);
		add_redirect(cmd, (t_redirect_type)rtype, filename->value);
		cur = filename->next;
	}
	*cursor = cur;
	return (1);
}

t_ast_node	*parse_command(t_token **tokens_ptr)
{
	t_command	*cmd;
	t_ast_node	*cmd_node;
	int			consumed;
	int			i;

	consumed = 0;
	cmd = create_command(*tokens_ptr, &consumed);
	if (!cmd)
		return (NULL);
	cmd_node = create_ast_node(NODE_COMMAND, cmd);
	if (!cmd_node)
		return (NULL);
	i = 0;
	while (i < consumed)
	{
		*tokens_ptr = (*tokens_ptr)->next;
		i++;
	}
	return (cmd_node);
}

t_ast_node	*parse_subshell(t_token **pp)
{
	t_ast_node	*inside;
	t_ast_node	*node;

	*pp = (*pp)->next;
	inside = parse_sequence(pp);
	if (!inside)
	{
		ft_fprintf(STDERR_FILENO, "Syntax error: empty or invalid subshell\n");
		return (NULL);
	}
	if (!*pp || (*pp)->type != T_CLOSE_PAREN)
	{
		free_ast(inside);
		errno = EAGAIN;
		return (NULL);
	}
	*pp = (*pp)->next;
	node = create_ast_node(NODE_SUBSHELL, NULL);
	node->left = inside;
	return (node);
}
