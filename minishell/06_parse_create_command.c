/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_parse_create_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:06:30 by tmura             #+#    #+#             */
/*   Updated: 2025/09/03 15:58:52 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_any(t_command *cmd, char *val, int *argc, int *cap)
{
	if (contains_wildcard(val) && !had_quote(val))
		return (append_wildcard(cmd, val, argc, cap));
	return (append_plain(cmd, val, argc, cap));
}

t_command	*cmd_fail(t_command *cmd, int argc)
{
	free_args_partial(cmd->args, argc);
	free(cmd->args);
	free(cmd);
	return (NULL);
}

t_command	*create_command(t_token *tokens, int *consumed)
{
	t_command	*cmd;
	t_token		*cur;
	int			argc;
	int			cap;
	int			used;

	argc = 0;
	cmd = init_command(&cap);
	if (!cmd)
		return (NULL);
	cur = tokens;
	used = parse_tokens_into_cmd(cmd, &cur, &argc, &cap);
	if (used < 0)
		return (cmd_fail(cmd, argc));
	cmd->args[argc] = NULL;
	if (consumed)
		*consumed = used;
	if (argc > 0 && cmd->args[0])
		cmd->builtin = identify_builtin(cmd->args[0]);
	return (cmd);
}

t_token	*skip_command_tokens(t_token *t)
{
	while (t && t->type == T_WORD)
	{
		t = t->next;
	}
	return (t);
}

void	add_redirect(t_command *cmd, t_redirect_type type, const char *target)
{
	t_redirect	*redir;
	t_redirect	*cur;

	if (!cmd)
		return ;
	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return ;
	redir->type = type;
	redir->filename = ft_strdup(target);
	redir->next = NULL;
	if (!cmd->redirects)
	{
		cmd->redirects = redir;
	}
	else
	{
		cur = cmd->redirects;
		while (cur->next)
			cur = cur->next;
		cur->next = redir;
	}
}
