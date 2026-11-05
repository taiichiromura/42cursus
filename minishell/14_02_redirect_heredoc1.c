/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_02_redirect_heredoc1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:07:10 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/15 20:25:11 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_child_status_and_redirect(t_heredoc_context *hdoc_ctx)
{
	int	fd_tmp;

	if (WIFSIGNALED(hdoc_ctx->status))
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		unlink(hdoc_ctx->tmp_filename);
		hdoc_ctx->shell_context->last_exit_status = 130;
		return (1);
	}
	fd_tmp = open(hdoc_ctx->tmp_filename, O_RDONLY);
	if (fd_tmp == -1)
	{
		perror(hdoc_ctx->tmp_filename);
		unlink(hdoc_ctx->tmp_filename);
		return (1);
	}
	if (hdoc_ctx->do_redirect)
	{
		if (dup2(fd_tmp, STDIN_FILENO) == -1)
			return (hd_dup2_error(fd_tmp, hdoc_ctx->tmp_filename));
	}
	close(fd_tmp);
	unlink(hdoc_ctx->tmp_filename);
	return (0);
}

static int	execute_parent_heredoc(int fd_tmp, pid_t pid,
		t_heredoc_context *hdoc_ctx)
{
	close(fd_tmp);
	if (wait_for_child_heredoc(pid, &hdoc_ctx->status) == -1)
	{
		perror("waitpid");
		unlink(hdoc_ctx->tmp_filename);
		hdoc_ctx->shell_context->last_exit_status = 1;
		return (1);
	}
	if (check_child_status_and_redirect(hdoc_ctx) != 0)
	{
		return (hdoc_ctx->shell_context->last_exit_status);
	}
	return (0);
}

static int	handle_red_heredoc_parent(int fd_tmp, pid_t pid,
		t_heredoc_context *hdoc_ctx)
{
	int	status;

	(void)status;
	signal(SIGINT, SIG_IGN);
	status = execute_parent_heredoc(fd_tmp, pid, hdoc_ctx);
	setup_parent_signals();
	free(hdoc_ctx->tmp_filename);
	return (status);
}

static int	heredoc_setup(t_redirect *current, t_shell_context *context,
		t_heredoc_context *hdoc_ctx, int *fd_tmp)
{
	hdoc_ctx->do_redirect = current->is_last_heredoc;
	hdoc_ctx->shell_context = context;
	if (prepare_heredoc_file(&hdoc_ctx->tmp_filename, fd_tmp) != 0)
	{
		context->last_exit_status = 1;
		return (1);
	}
	return (0);
}

int	handle_red_heredoc(t_redirect *current, char **envp,
		t_shell_context *context)
{
	int					fd_tmp;
	pid_t				pid;
	t_heredoc_context	hdoc_ctx;

	if (heredoc_setup(current, context, &hdoc_ctx, &fd_tmp) != 0)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		close(fd_tmp);
		free(hdoc_ctx.tmp_filename);
		context->last_exit_status = 1;
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execute_child_heredoc(current->filename, fd_tmp, envp, context);
	}
	else
		return (handle_red_heredoc_parent(fd_tmp, pid, &hdoc_ctx));
	return (0);
}
