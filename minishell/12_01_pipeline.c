/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_01_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:27:48 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/17 16:20:11 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipe_child(t_pipeline_context *p_ctx)
{
	handle_pipe_redirection(p_ctx->pipe_in, p_ctx->pipe_out);
	handle_redirections_execution(p_ctx->cmd_list, p_ctx->env_list,
		p_ctx->context);
}

void	execute_pipe_parents(t_pipeline_context *p_ctx)
{
	if (p_ctx->pipe_in[0] != -1)
	{
		close(p_ctx->pipe_in[0]);
		close(p_ctx->pipe_in[1]);
	}
	p_ctx->pipe_in[0] = p_ctx->pipe_out[0];
	p_ctx->pipe_in[1] = p_ctx->pipe_out[1];
}

pid_t	execute_pipe_loop(t_pipeline_context *p_ctx)
{
	pid_t	pid;

	if (p_ctx->cmd_list->next != NULL)
	{
		if (pipe(p_ctx->pipe_out) == -1)
			pipe_error();
	}
	else
	{
		p_ctx->pipe_out[0] = -1;
		p_ctx->pipe_out[1] = -1;
	}
	pid = fork();
	if (pid == -1)
		fork_error();
	if (pid == 0)
		execute_pipe_child(p_ctx);
	else
		execute_pipe_parents(p_ctx);
	return (pid);
}

int	execute_pipeline(t_command *cmd_list, t_env_var **env_list,
		t_shell_context *context)
{
	t_pipeline_context	p_ctx;
	pid_t				last_pid;

	if (cmd_list != NULL && cmd_list->next == NULL
		&& identify_builtin(cmd_list->args[0]))
	{
		return (execute_builtin(cmd_list, env_list, context));
	}
	p_ctx.cmd_list = cmd_list;
	p_ctx.env_list = env_list;
	p_ctx.context = context;
	p_ctx.pipe_in[0] = -1;
	p_ctx.pipe_in[1] = -1;
	while (p_ctx.cmd_list != NULL)
	{
		last_pid = execute_pipe_loop(&p_ctx);
		p_ctx.cmd_list = p_ctx.cmd_list->next;
	}
	if (p_ctx.pipe_in[0] != -1)
	{
		close(p_ctx.pipe_in[0]);
		close(p_ctx.pipe_in[1]);
	}
	return (wait_all_child_get_last_status(last_pid, context));
}
