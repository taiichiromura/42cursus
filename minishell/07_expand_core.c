/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expand_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:44:22 by tmura             #+#    #+#             */
/*   Updated: 2025/09/17 14:57:41 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strv_count(char **v)
{
	int	i;

	i = 0;
	while (v && v[i])
		i++;
	return (i);
}

char	**grow_out(char **out, int need, int *capacity, int used)
{
	char	**tmp;
	int		new_capacity;

	if (used + need + 1 <= *capacity)
		return (out);
	if (*capacity == 0)
		new_capacity = 16;
	else
		new_capacity = *capacity * 2;
	while (new_capacity < used + need + 1)
		new_capacity *= 2;
	tmp = (char **)ft_calloc(new_capacity, sizeof(char *));
	if (!tmp)
		return (NULL);
	if (out != NULL && used > 0)
		ft_memcpy(tmp, out, used * sizeof(char *));
	free(out);
	*capacity = new_capacity;
	return (tmp);
}

static int	append_one(char ***pout, int *used, int *cap, char *str)
{
	*pout = grow_out(*pout, 1, cap, *used);
	if (!*pout)
		return (free(str), 1);
	(*pout)[(*used)++] = str;
	return (0);
}

static int	append_matches_dup(char ***pout, int *used,
								int *cap, char **matched_str)
{
	int	i;

	i = 0;
	while (matched_str && matched_str[i])
	{
		*pout = grow_out(*pout, 1, cap, *used);
		if (!*pout)
			return (1);
		(*pout)[*used] = ft_strdup(matched_str[i]);
		if (!(*pout)[*used])
			return (1);
		*used += 1;
		i++;
	}
	return (0);
}

int	process_one(t_buildctx *ctx, char *raw,
		t_shell_context *context)
{
	int		quoted;
	char	*noquote;
	char	**matched_str;

	quoted = had_quote(raw);
	noquote = expand_params_keep_quotes(raw, ctx->env, context);
	if (!noquote || remove_quotes_inplace(&noquote) != 0)
		return (free(noquote), 1);
	if (!quoted && contains_wildcard(noquote))
	{
		matched_str = expand_wildcard_token(noquote);
		if (!matched_str)
			return (append_one(ctx->out_ref,
					ctx->n_ref, ctx->cap_ref, noquote));
		if (append_matches_dup(ctx->out_ref, ctx->n_ref,
				ctx->cap_ref, matched_str))
			return (free(noquote), free_strv(matched_str), 1);
		free(noquote);
		free_strv(matched_str);
		return (0);
	}
	return (append_one(ctx->out_ref, ctx->n_ref, ctx->cap_ref, noquote));
}
