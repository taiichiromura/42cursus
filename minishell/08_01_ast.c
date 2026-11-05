/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_01_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:54:36 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/15 20:06:17 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipe_node(t_ast_node *node, t_env_var **env_list,
		t_shell_context *context)
{
	t_command	*cmd_list;
	int			exit_status;

	cmd_list = ast_to_command_list(node);
	if (!cmd_list)
		return (1);
	exit_status = execute_pipeline(cmd_list, env_list, context);
	free_command_list(cmd_list);
	return (exit_status);
}

int	execute_logical_and(t_ast_node *node, t_env_var **env_list,
		t_shell_context *context)
{
	if (execute_ast(node->left, env_list, context) == 0)
		return (execute_ast(node->right, env_list, context));
	return (1);
}

int	execute_logical_or(t_ast_node *node, t_env_var **env_list,
		t_shell_context *context)
{
	if (execute_ast(node->left, env_list, context) != 0)
		return (execute_ast(node->right, env_list, context));
	return (0);
}

int	execute_sequence_node(t_ast_node *node, t_env_var **env_list,
		t_shell_context *context)
{
	int	exit_status;

	exit_status = execute_ast(node->left, env_list, context);
	if (context->last_exit_status != 130 && context->last_exit_status != 131)
		return (execute_ast(node->right, env_list, context));
	return (exit_status);
}

int	execute_ast(t_ast_node *node, t_env_var **env_list,
		t_shell_context *context)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (execute_command(node->cmd, env_list, context));
	else if (node->type == NODE_PIPE)
		return (execute_pipe_node(node, env_list, context));
	else if (node->type == NODE_AND)
		return (execute_logical_and(node, env_list, context));
	else if (node->type == NODE_OR)
		return (execute_logical_or(node, env_list, context));
	else if (node->type == NODE_SUBSHELL)
		return (execute_subshell(node->left, env_list, context));
	else if (node->type == NODE_SEQUENCE)
		return (execute_sequence_node(node, env_list, context));
	else
		return (1);
}
