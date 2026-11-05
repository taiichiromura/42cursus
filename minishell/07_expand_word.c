/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expand_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:56:50 by tmura             #+#    #+#             */
/*   Updated: 2025/09/18 16:24:20 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	step_quote(char character, int *quote_status, char **quoted_word)
{
	if (*quote_status == 0 && (character == '\'' || character == '\"'))
	{
		if (character == '\'')
			*quote_status = 1;
		else
			*quote_status = 2;
		*quoted_word = pushc(*quoted_word, character);
		return (1);
	}
	if ((*quote_status == 1 && character == '\'') || (*quote_status == 2
			&& character == '\"'))
	{
		*quote_status = 0;
		*quoted_word = pushc(*quoted_word, character);
		return (1);
	}
	return (0);
}

static int	step_dollar(t_dollarctx *ctx, t_shell_context *context)
{
	char	*tmp;
	size_t	n;

	if (ctx->q == 1 || ctx->raw[*(ctx->i)] != '$')
		return (0);
	*(ctx->i) += 1;
	if (ctx->raw[*(ctx->i)] == '?')
	{
		tmp = itoa_status(context->last_exit_status);
		*(ctx->out) = pushs(*(ctx->out), tmp);
		free(tmp);
		*(ctx->i) += 1;
		return (1);
	}
	n = read_name(ctx->raw, *(ctx->i));
	if (n == 0)
	{
		*(ctx->out) = pushc(*(ctx->out), '$');
		return (1);
	}
	tmp = ft_strndup(ctx->raw + *(ctx->i), n);
	*(ctx->out) = pushs(*(ctx->out), my_getenv_val(ctx->env, tmp));
	free(tmp);
	*(ctx->i) += n;
	return (1);
}

static int	expand_step(t_dollarctx *dctx, int *quote, t_shell_context *context)
{
	if (step_quote(dctx->raw[*(dctx->i)], quote, dctx->out))
	{
		dctx->q = *quote;
		*(dctx->i) += 1;
		return (0);
	}
	dctx->q = *quote;
	if (step_dollar(dctx, context))
		return (0);
	*(dctx->out) = pushc(*(dctx->out), dctx->raw[*(dctx->i)]);
	if (!*(dctx->out))
		return (1);
	*(dctx->i) += 1;
	return (0);
}

char	*expand_params_keep_quotes(const char *raw, t_env_var *env,
		t_shell_context *context)
{
	size_t		i;
	int			quote;
	char		*out;
	t_dollarctx	dctx;

	i = 0;
	quote = 0;
	out = NULL;
	dctx.raw = raw;
	dctx.i = &i;
	dctx.q = quote;
	dctx.out = &out;
	dctx.env = env;
	while (raw[i])
	{
		if (expand_step(&dctx, &quote, context))
			return (NULL);
	}
	if (!out)
		out = ft_strdup("");
	return (out);
}
