/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_02_lexer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:24:54 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/15 20:13:39 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, const char *start, size_t len)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	tok->type = type;
	tok->value = ft_strndup(start, len);
	tok->next = NULL;
	return (tok);
}

void	add_token(t_token **head, t_token *new_tok)
{
	t_token	*cur;

	if (!*head)
		*head = new_tok;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new_tok;
	}
}

t_token	*handle_single1(const char *line, size_t *i)
{
	if (line[*i] == '|')
	{
		*i += 1;
		return (new_token(T_PIPE, "|", 1));
	}
	if (line[*i] == '<')
	{
		*i += 1;
		return (new_token(T_REDIR_IN, "<", 1));
	}
	if (line[*i] == '>')
	{
		*i += 1;
		return (new_token(T_REDIR_OUT, ">", 1));
	}
	return (NULL);
}

t_token	*handle_single2(const char *line, size_t *i)
{
	if (line[*i] == ';' || line[*i] == '\n')
	{
		*i += 1;
		return (new_token(T_SEMI, ";", 1));
	}
	if (line[*i] == '(')
	{
		*i += 1;
		return (new_token(T_OPEN_PAREN, "(", 1));
	}
	if (line[*i] == ')')
	{
		*i += 1;
		return (new_token(T_CLOSE_PAREN, ")", 1));
	}
	return (NULL);
}
