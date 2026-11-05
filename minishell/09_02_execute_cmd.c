/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_02_execute_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:22:52 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/17 16:16:02 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_command_without_redirect(t_command *cmd,
		t_env_var **env_list, t_shell_context *context)
{
	int	exit_status;

	if (cmd->builtin != BUILTIN_NONE)
	{
		if (cmd->builtin == BUILTIN_EXIT)
			ft_fprintf(STDERR_FILENO, "exit\n");
		exit_status = execute_builtin(cmd, env_list, context);
	}
	else
		exit_status = execute_external_command(cmd, *env_list, context);
	context->last_exit_status = exit_status;
	return (exit_status);
}

static int	prepare_and_handle_redirects(t_exec_context *exec_ctx,
		int *saved_stdin, int *saved_stdout)
{
	char	**envp_array;

	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		exec_ctx->shell_context->last_exit_status = 1;
		return (1);
	}
	envp_array = generate_envp_for_execve(*(exec_ctx->env_list));
	if (handle_redirection(exec_ctx->cmd->redirects, envp_array,
			exec_ctx->shell_context) != 0)
	{
		free_array(envp_array);
		return (1);
	}
	free_array(envp_array);
	return (0);
}

static void	restore_and_cleanup(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static int	execute_command_with_redirect(t_command *cmd, t_env_var **env_list,
		t_shell_context *context)
{
	int				saved_stdin;
	int				saved_stdout;
	int				exit_status;
	t_exec_context	exec_ctx;

	exec_ctx.cmd = cmd;
	exec_ctx.env_list = env_list;
	exec_ctx.shell_context = context;
	if (prepare_and_handle_redirects(&exec_ctx, &saved_stdin,
			&saved_stdout) != 0)
	{
		restore_and_cleanup(saved_stdin, saved_stdout);
		return (1);
	}
	exit_status = execute_builtin(cmd, env_list, context);
	restore_and_cleanup(saved_stdin, saved_stdout);
	context->last_exit_status = exit_status;
	return (exit_status);
}

int	execute_with_redirect(t_command *cmd, t_env_var **env_list,
		t_shell_context *context)
{
	if (cmd->redirects == NULL)
		return (execute_command_without_redirect(cmd, env_list, context));
	else
	{
		if (cmd->builtin != BUILTIN_NONE)
			return (execute_command_with_redirect(cmd, env_list, context));
		else
			return (execute_external_command(cmd, *env_list, context));
	}
}
