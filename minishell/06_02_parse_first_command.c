/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_02_parse_first_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:50:14 by tmura             #+#    #+#             */
/*   Updated: 2025/08/27 17:23:01 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_command_or_subshell(t_token **pp)
{
	t_ast_node	*node;

	if (*pp && (*pp)->type == T_OPEN_PAREN)
	{
		node = parse_subshell(pp);
		if (!node)
			return (NULL);
		return (node);
	}
	return (parse_command(pp));
}

t_ast_node	*free_and_error(t_ast_node *node)
{
	ft_fprintf(STDERR_FILENO, "Syntax error: expected command after pipe\n");
	free_ast(node);
	return (NULL);
}

int	is_invalid_pipe_syntax(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == T_PIPE || token->type == T_SEMI
		|| token->type == T_AND || token->type == T_OR
		|| token->type == T_CLOSE_PAREN)
		return (1);
	return (0);
}

t_ast_node	*parse_pipeline_loop(t_token **tokens_ptr, t_ast_node *left)
{
	t_ast_node	*right;
	t_ast_node	*pipe;

	while (*tokens_ptr && (*tokens_ptr)->type == T_PIPE)
	{
		*tokens_ptr = (*tokens_ptr)->next;
		if (is_invalid_pipe_syntax(*tokens_ptr))
			return (free_and_error(left));
		right = parse_command_or_subshell(tokens_ptr);
		if (!right)
			return (free_and_error(left));
		pipe = create_ast_node(NODE_PIPE, NULL);
		pipe->left = left;
		pipe->right = right;
		left = pipe;
	}
	return (left);
}

t_ast_node	*parse_first_command(t_token **tokens_ptr)
{
	t_ast_node	*node;

	node = parse_command_or_subshell(tokens_ptr);
	if (!node)
		return (NULL);
	return (node);
}
