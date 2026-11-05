/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expand_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:39:22 by tmura             #+#    #+#             */
/*   Updated: 2025/09/17 14:58:33 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_command(t_command *cmd, t_env_var *env,
				t_shell_context *context);

int	expand_ast(t_ast_node *node, t_env_var *env, t_shell_context *context)
{
	int	result;

	if (!node)
		return (0);
	if (node->type == NODE_COMMAND && node->cmd)
		return (expand_command(node->cmd, env, context));
	result = 0;
	if (node->left)
	{
		result = expand_ast(node->left, env, context);
		if (result != 0)
			return (result);
	}
	if (node->right)
		result = expand_ast(node->right, env, context);
	return (result);
}

static int	expand_command(t_command *cmd, t_env_var *env,
			t_shell_context *context)
{
	if (!cmd)
		return (0);
	if (expand_args(&cmd->args, env, context) != 0)
	{
		return (1);
	}
	if (expand_redirects(cmd->redirects, env, context) != 0)
		return (1);
	return (0);
}
