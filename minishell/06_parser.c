/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 19:12:46 by tmura             #+#    #+#             */
/*   Updated: 2025/08/29 17:46:03 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_ast_node(t_node_type type, t_command *cmd)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_command	*init_command(int *cap)
{
	t_command	*cmd;

	*cap = 4;
	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_command));
	cmd->args = (char **)malloc(sizeof(char *) * (*cap));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->redirects = NULL;
	return (cmd);
}

t_builtin_type	identify_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (BUILTIN_ECHO);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (BUILTIN_CD);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (BUILTIN_PWD);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (BUILTIN_EXPORT);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (BUILTIN_UNSET);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (BUILTIN_ENV);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (BUILTIN_EXIT);
	return (BUILTIN_NONE);
}
