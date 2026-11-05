/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_02_ast_newlist2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:28:55 by ktakeru           #+#    #+#             */
/*   Updated: 2025/08/21 18:43:57 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirect	*create_new_redirect_node(t_redirect *original)
{
	t_redirect	*new_redir;

	new_redir = malloc(sizeof(t_redirect));
	if (!new_redir)
		return (NULL);
	ft_bzero(new_redir, sizeof(t_redirect));
	new_redir->type = original->type;
	new_redir->filename = ft_strdup(original->filename);
	if (!new_redir->filename)
	{
		free(new_redir);
		return (NULL);
	}
	return (new_redir);
}

static void	add_redirect_to_list(t_redirect **list, t_redirect **tail,
		t_redirect *redir)
{
	redir->next = NULL;
	if (!*list)
	{
		*list = redir;
		*tail = redir;
	}
	else
	{
		(*tail)->next = redir;
		*tail = redir;
	}
}

t_redirect	*copy_redirects(t_redirect *original)
{
	t_redirect	*new_list;
	t_redirect	*new_tail;
	t_redirect	*current;
	t_redirect	*new_redir;

	new_list = NULL;
	new_tail = NULL;
	current = original;
	while (current)
	{
		new_redir = create_new_redirect_node(current);
		if (!new_redir)
			return (free_redirects(new_list), NULL);
		add_redirect_to_list(&new_list, &new_tail, new_redir);
		current = current->next;
	}
	return (new_list);
}
