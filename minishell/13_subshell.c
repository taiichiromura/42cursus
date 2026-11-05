/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:00:59 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/15 20:33:04 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_wait_status(int status)
{
	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_fprintf(STDERR_FILENO, "\n");
			return (130);
		}
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	execute_subshell(t_ast_node *subshell_node, t_env_var **env_list,
		t_shell_context *context)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		execute_ast(subshell_node->left, env_list, context);
		exit(context->last_exit_status);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			context->last_exit_status = 1;
			return (1);
		}
		return (handle_wait_status(status));
	}
}
