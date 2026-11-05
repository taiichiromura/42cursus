/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_quote_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 23:15:18 by tmura             #+#    #+#             */
/*   Updated: 2025/09/03 14:57:00 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_esc_target(int character)
{
	return (character == '\"' || character == '$'
		|| character == '\\' || character == '`');
}

static char	*qr_push(char *str, char character)
{
	char	*new_str;
	size_t	len;
	char	tmp[2];

	if (!str)
	{
		tmp[0] = character;
		tmp[1] = '\0';
		return (ft_strdup(tmp));
	}
	len = ft_strlen(str);
	new_str = (char *)malloc(len + 2);
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, str);
	new_str[len] = character;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}

int	rq_try_open_or_close(int *quote, char character, size_t *i)
{
	if (*quote == IN_NONE)
	{
		if (character == '\'')
		{
			*quote = IN_SQ;
			(*i)++;
			return (1);
		}
		if (character == '\"')
		{
			*quote = IN_DQ;
			(*i)++;
			return (1);
		}
	}
	else if ((*quote == IN_SQ && character == '\'')
		|| (*quote == IN_DQ && character == '\"'))
	{
		*quote = IN_NONE;
		(*i)++;
		return (1);
	}
	return (0);
}

int	rq_try_dq_escape(const char *str, size_t *i, int quote, char **out)
{
	char	*tmp;

	if (quote != IN_DQ)
		return (0);
	if (str[*i] != '\\' || str[*i + 1] == '\0')
		return (0);
	if (!is_esc_target(str[*i + 1]))
		return (0);
	tmp = qr_push(*out, str[*i + 1]);
	if (!tmp)
		return (-1);
	*out = tmp;
	*i += 2;
	return (1);
}

int	rq_emit_plain(const char *str, size_t *i, char **out)
{
	char	*tmp;

	tmp = qr_push(*out, str[*i]);
	if (!tmp)
		return (-1);
	*out = tmp;
	(*i)++;
	return (1);
}
