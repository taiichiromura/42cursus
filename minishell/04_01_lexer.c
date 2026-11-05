/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_01_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:54:05 by ktakeru           #+#    #+#             */
/*   Updated: 2025/08/27 17:23:25 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*handle_double_operator(const char *line, size_t *i)
{
	if (line[*i] == '&' && line[*i + 1] == '&')
	{
		*i += 2;
		return (new_token(T_AND, "&&", 2));
	}
	if (line[*i] == '|' && line[*i + 1] == '|')
	{
		*i += 2;
		return (new_token(T_OR, "||", 2));
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		*i += 2;
		return (new_token(T_REDIR_HEREDOC, "<<", 2));
	}
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		*i += 2;
		return (new_token(T_REDIR_APPEND, ">>", 2));
	}
	return (NULL);
}

static t_token	*handle_single_operator(const char *line, size_t *i)
{
	if ((line[*i] == '|') || (line[*i] == '<') || (line[*i] == '>'))
		return (handle_single1(line, i));
	else if ((line[*i] == ';') || (line[*i] == '(')
		|| (line[*i] == ')') || (line[*i] == '\n'))
		return (handle_single2(line, i));
	return (NULL);
}

static void	scan_word_end(const char *line, size_t *i)
{
	int				q;
	unsigned char	ch;

	q = 0;
	while (line[*i])
	{
		ch = (unsigned char)line[*i];
		if (q == 0 && (ch == '\'' || ch == '\"'))
		{
			if (ch == '\'')
				q = 1;
			else
				q = 2;
			(*i)++;
		}
		else if ((q == 1 && ch == '\'') || (q == 2 && ch == '\"'))
		{
			q = 0;
			(*i)++;
		}
		else if (q == 0 && (isspace(ch) || ft_strchr("|<>;()", ch) != NULL))
			break ;
		else
			(*i)++;
	}
}

static t_token	*handle_word(const char *line, size_t *i)
{
	size_t	start;

	start = *i;
	scan_word_end(line, i);
	return (new_token(T_WORD, line + start, *i - start));
}

t_token	*lexer(const char *line)
{
	t_token	*head;
	t_token	*new_token;
	size_t	i;

	head = NULL;
	i = 0;
	if (!line || !*line)
		return (NULL);
	while (line[i])
	{
		while (line[i] && ft_isspace((unsigned char)line[i]))
			i++;
		if (!line[i])
			break ;
		new_token = handle_double_operator(line, &i);
		if (!new_token)
			new_token = handle_single_operator(line, &i);
		if (!new_token)
			new_token = handle_word(line, &i);
		if (new_token)
			add_token(&head, new_token);
		else
			handle_lexer_error(head, line[i]);
	}
	return (head);
}
