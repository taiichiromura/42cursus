/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_02_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:01:08 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/15 20:32:17 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command_execution(t_command *current_cmd, t_env_var **env_list,
		t_shell_context *context)
{
	if (identify_builtin(current_cmd->args[0]))
	{
		exit(execute_builtin(current_cmd, env_list, context));
	}
	else
	{
		execute_child_process(current_cmd->args, *env_list,
			current_cmd->redirects, context);
		exit(127);
	}
}

void	handle_redirections_execution(t_command *cmd, t_env_var **env_list,
		t_shell_context *context)
{
	char	**envp_array;

	if (cmd->redirects != NULL)
	{
		envp_array = generate_envp_for_execve(*env_list);
		if (handle_redirection(cmd->redirects, envp_array, context) != 0)
		{
			free_array(envp_array);
			exit(context->last_exit_status);
		}
		free_array(envp_array);
	}
	handle_command_execution(cmd, env_list, context);
	exit(127);
}

void	handle_pipe_redirection(int *pipe_in, int *pipe_out)
{
	if (pipe_in[0] != -1)
	{
		if (dup2(pipe_in[0], STDIN_FILENO) == -1)
			exit(dup2_error());
	}
	if (pipe_out[1] != -1)
	{
		if (dup2(pipe_out[1], STDOUT_FILENO) == -1)
			exit(dup2_error());
	}
	if (pipe_in[0] != -1)
		close(pipe_in[0]);
	if (pipe_in[1] != -1)
		close(pipe_in[1]);
	if (pipe_out[0] != -1)
		close(pipe_out[0]);
	if (pipe_out[1] != -1)
		close(pipe_out[1]);
}

int	wait_all_child_get_last_status(pid_t last_pid, t_shell_context *context)
{
	int		status;
	pid_t	current_pid;
	int		last_exit_status;

	last_exit_status = 0;
	while (1)
	{
		current_pid = waitpid(-1, &status, 0);
		if (current_pid == -1)
		{
			if (errno == ECHILD)
				break ;
			perror("minishell: waitpid");
			break ;
		}
		if (current_pid == last_pid)
		{
			if (WIFEXITED(status))
				last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_exit_status = 128 + WTERMSIG(status);
		}
	}
	context->last_exit_status = last_exit_status;
	return (last_exit_status);
}
