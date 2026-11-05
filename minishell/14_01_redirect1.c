/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_01_redirect1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:58:09 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/15 20:01:01 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirection_type(t_redirect *current, char **envp,
		t_shell_context *context)
{
	if (current->type == RED_IN)
	{
		if (handle_red_in(current) == 1)
			return (1);
	}
	else if (current->type == RED_OUT)
	{
		if (handle_red_out(current) == 1)
			return (1);
	}
	else if (current->type == RED_APPEND)
	{
		if (handle_red_append(current) == 1)
			return (1);
	}
	else if (current->type == RED_HEREDOC)
	{
		if (handle_red_heredoc(current, envp, context) == 1)
			return (1);
	}
	return (0);
}

static void	set_last_heredoc_flag(t_redirect *redirect_list)
{
	t_redirect	*current;
	t_redirect	*last_heredoc;

	current = redirect_list;
	last_heredoc = NULL;
	while (current)
	{
		current->is_last_heredoc = 0;
		if (current->type == RED_HEREDOC)
			last_heredoc = current;
		current = current->next;
	}
	if (last_heredoc)
		last_heredoc->is_last_heredoc = 1;
}

int	handle_redirection(t_redirect *redirect_list, char **envp,
		t_shell_context *context)
{
	t_redirect	*current;
	int			ret;

	set_last_heredoc_flag(redirect_list);
	current = redirect_list;
	while (current)
	{
		ret = redirection_type(current, envp, context);
		if (ret == 1)
		{
			context->last_exit_status = 1;
			return (1);
		}
		if (g_sigint_received == 130)
		{
			context->last_exit_status = 130;
			return (1);
		}
		current = current->next;
	}
	return (0);
}
