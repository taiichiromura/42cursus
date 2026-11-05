/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expand_core02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:25:02 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/17 14:58:07 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	build_from_src(char **src, t_buildctx *ctx,
		t_shell_context *context)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		if (process_one(ctx, src[i], context) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	rebuild_args(char ***pargv, char **src, t_env_var *env,
		t_shell_context *context)
{
	int			n;
	int			capacity;
	char		**out;
	t_buildctx	ctx;

	n = 0;
	capacity = 0;
	out = NULL;
	ctx.out_ref = &out;
	ctx.n_ref = &n;
	ctx.cap_ref = &capacity;
	ctx.env = env;
	if (build_from_src(src, &ctx, context) != 0)
		return (free_args_partial(out, n), 1);
	out = grow_out(out, 0, &capacity, n);
	if (!out)
		return (1);
	out[n] = NULL;
	free_strv(*pargv);
	*pargv = out;
	return (0);
}

static int	redir_set_filename(t_redirect *r, const char *s)
{
	char	*dup;

	dup = ft_strdup(s);
	if (!dup)
		return (1);
	free(r->filename);
	r->filename = dup;
	return (0);
}

static int	print_ambiguous_and_fail(char **m, char *noq,
		t_shell_context *context)
{
	free_strv(m);
	free(noq);
	ft_fprintf(2, "minishell: ambiguous redirect\n");
	context->last_exit_status = 1;
	return (1);
}

int	handle_wildcard_redir(t_redirect *r, char *noq, t_shell_context *context)
{
	char		**m;
	int			cnt;
	int			rc;

	m = expand_wildcard_token(noq);
	if (!m)
	{
		free(noq);
		return (0);
	}
	cnt = strv_count(m);
	if (cnt != 1)
		return (print_ambiguous_and_fail(m, noq, context));
	rc = redir_set_filename(r, m[0]);
	free_strv(m);
	free(noq);
	return (rc);
}
