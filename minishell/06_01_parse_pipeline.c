/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_01_parse_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:50:06 by tmura             #+#    #+#             */
/*   Updated: 2025/08/27 16:53:12 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_pipeline(t_token **tokens_ptr)
{
	t_ast_node	*left;

	left = parse_first_command(tokens_ptr);
	if (!left)
		return (NULL);
	return (parse_pipeline_loop(tokens_ptr, left));
}

t_ast_node	*parse_or(t_token **tokens_ptr)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*node;

	left = parse_and(tokens_ptr);
	if (!left)
		return (NULL);
	while (*tokens_ptr && (*tokens_ptr)->type == T_OR)
	{
		*tokens_ptr = (*tokens_ptr)->next;
		right = parse_and(tokens_ptr);
		if (!right)
		{
			ft_fprintf(STDERR_FILENO,
				"syntax error: expected command after ||\n");
			return (NULL);
		}
		node = create_ast_node(NODE_OR, NULL);
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

t_ast_node	*parse_and(t_token **tokens_ptr)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*node;

	left = parse_pipeline(tokens_ptr);
	if (!left)
		return (NULL);
	while (*tokens_ptr && (*tokens_ptr)->type == T_AND)
	{
		*tokens_ptr = (*tokens_ptr)->next;
		right = parse_pipeline(tokens_ptr);
		if (!right)
		{
			ft_fprintf(STDERR_FILENO,
				"syntax error: expected command after &&\n");
			return (NULL);
		}
		node = create_ast_node(NODE_AND, NULL);
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

t_ast_node	*parse_sequence(t_token **tokens_ptr)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*seq_node;

	left = parse_or(tokens_ptr);
	if (!left)
		return (NULL);
	while (*tokens_ptr && (*tokens_ptr)->type == T_SEMI)
	{
		*tokens_ptr = (*tokens_ptr)->next;
		right = parse_or(tokens_ptr);
		if (!right)
		{
			ft_fprintf(STDERR_FILENO,
				"Syntax error: empty command after ';'\n");
			free_ast(left);
			return (NULL);
		}
		seq_node = create_ast_node(NODE_SEQUENCE, NULL);
		seq_node->left = left;
		seq_node->right = right;
		left = seq_node;
	}
	return (left);
}

t_ast_node	*parse_tokens(t_token *tokens)
{
	return (parse_sequence(&tokens));
}
