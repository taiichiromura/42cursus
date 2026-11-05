/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_quote_remove02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:29:59 by tmura             #+#    #+#             */
/*   Updated: 2025/08/26 12:30:33 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	rq_step(const char *str, size_t *i, int *quote, char **out)
{
	int	result;

	result = rq_try_open_or_close(quote, str[*i], i);
	if (result != 0)
	{
		if (result == 1)
			return (1);
		else
			return (-1);
	}
	result = rq_try_dq_escape(str, i, *quote, out);
	if (result != 0)
		return (result);
	return (rq_emit_plain(str, i, out));
}

int	remove_quotes_inplace(char **strs)
{
	size_t	i;
	int		quote;
	char	*out;
	int		result;

	if (!strs || !*strs)
		return (0);
	i = 0;
	quote = IN_NONE;
	out = NULL;
	while ((*strs)[i])
	{
		result = rq_step(*strs, &i, &quote, &out);
		if (result < 0)
			return (free(out), 1);
	}
	free(*strs);
	if (!out)
		out = ft_strdup("");
	*strs = out;
	return (*strs == NULL);
}

int	had_quote(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}
