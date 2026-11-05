/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_01_external_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:57:55 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/18 16:12:07 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_error_and_exit(char *cmd, int exit_status,
		t_env_var *env_list)
{
	if (exit_status == 126)
		ft_fprintf(STDERR_FILENO, "bash: %s: Permission denied\n", cmd);
	else if (exit_status == 127)
	{
		if (ft_strchr(cmd, '/') != NULL || my_getenv_val(env_list,
				"PATH") == NULL)
			ft_fprintf(STDERR_FILENO, "bash: %s: No such file or directory\n",
				cmd);
		else
			ft_fprintf(STDERR_FILENO, "%s: command not found\n", cmd);
	}
	exit(exit_status);
}

void	execute_child_process(char **argv, t_env_var *env_list,
		t_redirect *redirect_list, t_shell_context *context)
{
	char	*cmd_path;
	char	**envp_array;
	int		exit_status;

	setup_child_signals();
	envp_array = generate_envp_for_execve(env_list);
	if (redirect_list != NULL)
	{
		if (handle_redirection(redirect_list, envp_array, context) != 0)
		{
			free_array(envp_array);
			exit(context->last_exit_status);
		}
	}
	exit_status = find_command_path(argv[0], env_list, &cmd_path);
	if (exit_status != 0)
	{
		handle_error_and_exit(argv[0], exit_status, env_list);
	}
	execve(cmd_path, argv, envp_array);
	perror("bash: execve failed");
	free(cmd_path);
	free_array(envp_array);
	exit(126);
}

static int	analyze_exit_status(int status, t_shell_context *context)
{
	int	sig;

	if (WIFEXITED(status))
	{
		context->last_exit_status = WEXITSTATUS(status);
		return (context->last_exit_status);
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		context->last_exit_status = 128 + sig;
		if (sig == SIGINT)
		{
			g_sigint_received = 130;
			write(STDOUT_FILENO, "\n", 1);
		}
		else if (sig == SIGQUIT)
		{
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		}
		return (context->last_exit_status);
	}
	return (1);
}

static int	execute_parent_wait(pid_t pid, t_shell_context *context)
{
	int	status;
	int	result;

	while (1)
	{
		result = waitpid(pid, &status, 0);
		if (result == -1 && errno == EINTR)
			continue ;
		if (result != -1)
			break ;
	}
	if (result == -1)
		return (1);
	return (analyze_exit_status(status, context));
}

int	execute_external_command(t_command *cmd, t_env_var *env_list,
		t_shell_context *context)
{
	pid_t	pid;
	int		exit_status;

	setup_parent_wait_signals();
	pid = fork();
	if (pid == -1)
	{
		setup_parent_signals();
		perror("minishell: fork");
		context->last_exit_status = 1;
		return (1);
	}
	else if (pid == 0)
	{
		execute_child_process(cmd->args, env_list, cmd->redirects, context);
		exit(1);
	}
	exit_status = execute_parent_wait(pid, context);
	setup_parent_signals();
	return (exit_status);
}
