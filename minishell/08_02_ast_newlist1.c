/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_02_ast_newlist1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:10:49 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/03 16:06:36 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_command_args(t_command *new_cmd, t_command *original_cmd)
{
	int	i;
	int	arg_count;

	arg_count = 0;
	while (original_cmd->args[arg_count])
		arg_count++;
	new_cmd->args = malloc((arg_count + 1) * sizeof(char *));
	if (!new_cmd->args)
		return (-1);
	ft_bzero(new_cmd->args, (arg_count + 1) * sizeof(char *));
	i = 0;
	while (original_cmd->args[i])
	{
		new_cmd->args[i] = ft_strdup(original_cmd->args[i]);
		if (!new_cmd->args[i])
		{
			free_array(new_cmd->args);
			return (-1);
		}
		i++;
	}
	return (0);
}

t_command	*create_new_command(t_ast_node *node)
{
	t_command	*new_cmd;

	if (!node || !node->cmd)
		return (NULL);
	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	ft_bzero(new_cmd, sizeof(t_command));
	if (copy_command_args(new_cmd, node->cmd) == -1)
	{
		free(new_cmd);
		return (NULL);
	}
	new_cmd->builtin = node->cmd->builtin;
	new_cmd->redirects = copy_redirects(node->cmd->redirects);
	if (node->cmd->redirects && !new_cmd->redirects)
	{
		free_array(new_cmd->args);
		free(new_cmd);
		return (NULL);
	}
	return (new_cmd);
}

static t_command	*handle_pipe_node(t_ast_node *node)
{
	t_command	*cmd_list;
	t_command	*next_cmd;
	t_command	*tail;

	cmd_list = ast_to_command_list(node->left);
	if (!cmd_list)
		return (NULL);
	next_cmd = ast_to_command_list(node->right);
	if (!next_cmd)
	{
		free_command_list(cmd_list);
		return (NULL);
	}
	tail = cmd_list;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = next_cmd;
	return (cmd_list);
}

t_command	*ast_to_command_list(t_ast_node *node)
{
	if (!node)
		return (NULL);
	if (node->type == NODE_COMMAND)
		return (create_new_command(node));
	else if (node->type == NODE_PIPE)
		return (handle_pipe_node(node));
	return (NULL);
}
