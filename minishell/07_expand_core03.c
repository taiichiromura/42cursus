/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expand_core03.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:50:58 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/17 14:57:26 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_one_redir(t_redirect *redir, t_env_var *env,
		t_shell_context *context)
{
	int		quote;
	char	*mid;
	char	*no_quote;

	if (redir->type == RED_HEREDOC)
		return (0);
	quote = had_quote(redir->filename);
	mid = expand_params_keep_quotes(redir->filename, env, context);
	if (!mid)
		return (1);
	no_quote = ft_strdup(mid);
	free(mid);
	if (!no_quote || remove_quotes_inplace(&no_quote) != 0)
	{
		free(no_quote);
		return (1);
	}
	if (!quote && contains_wildcard(no_quote))
		return (handle_wildcard_redir(redir, no_quote, context));
	free(redir->filename);
	redir->filename = no_quote;
	return (redir->filename == NULL);
}

int	expand_redirects(t_redirect *redir, t_env_var *env,
		t_shell_context *context)
{
	while (redir)
	{
		if (expand_one_redir(redir, env, context) != 0)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	expand_args(char ***pargv, t_env_var *env, t_shell_context *context)
{
	char	**src;

	src = *pargv;
	if (!src)
		return (0);
	return (rebuild_args(pargv, src, env, context));
}
