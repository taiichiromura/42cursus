/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_01_validate_syntax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:16:22 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/18 16:34:32 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	synerr(int kind, const char *a, const char *b)
{
	if (kind == ERR_START)
		ft_fprintf(STDERR_FILENO,
			"syntax error: unexpected token '%s' at start\n", a);
	else if (kind == ERR_REDIR)
		ft_fprintf(STDERR_FILENO,
			"bash: syntax error near unexpected token `newline'\n");
	else if (kind == ERR_PIPE)
		ft_fprintf(STDERR_FILENO,
			"syntax error: expected command after pipe '|'\n");
	else if (kind == ERR_TWOOPS)
		ft_fprintf(STDERR_FILENO,
			"syntax error: unexpected token '%s' after '%s'\n", a, b);
	else if (kind == ERR_OPEN_PAREN)
		ft_fprintf(STDERR_FILENO,
			"bash: syntax error near unexpected token '%s'\n", a);
	else if (kind == ERR_CLOSE_PAREN)
		ft_fprintf(STDERR_FILENO,
			"bash: syntax error near unexpected token '%s'\n", a);
	return (1);
}

static int	check_token(t_token *prev, t_token *cur, int *open_paren)
{
	if (is_redir(cur->type) && (!cur->next || cur->next->type != T_WORD))
		return (synerr(ERR_REDIR, cur->value, NULL));
	if (cur->type == T_PIPE && (!cur->next
			|| !is_cmd_start_token(cur->next->type)))
		return (synerr(ERR_PIPE, NULL, NULL));
	if (prev && is_op(prev->type) && is_op(cur->type))
		return (synerr(ERR_TWOOPS, cur->value, prev->value));
	if (prev && prev->type == T_WORD && cur->type == T_OPEN_PAREN)
		return (synerr(ERR_OPEN_PAREN, cur->value, prev->value));
	if (cur->type == T_OPEN_PAREN)
		(*open_paren)++;
	else if (cur->type == T_CLOSE_PAREN)
	{
		if (*open_paren <= 0)
			return (synerr(ERR_CLOSE_PAREN, cur->value, NULL));
		(*open_paren)--;
	}
	return (0);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*prev;
	t_token	*cur;
	int		open_paren;
	int		rc;

	prev = NULL;
	cur = tokens;
	open_paren = 0;
	if (!cur)
		return (0);
	if (is_op(cur->type))
		return (synerr(ERR_START, cur->value, NULL));
	while (cur)
	{
		rc = check_token(prev, cur, &open_paren);
		if (rc)
			return (rc);
		prev = cur;
		cur = cur->next;
	}
	if (open_paren > 0)
		return (2);
	return (0);
}
