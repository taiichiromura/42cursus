/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ctl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:54:16 by tmura             #+#    #+#             */
/*   Updated: 2025/07/10 13:54:27 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_list_ps	*new_node(int value)
{
	t_list_ps	*node;

	node = malloc(sizeof(t_list_ps));
	if (!node)
		exit(1);
	node->value = value;
	node->next = NULL;
	return (node);
}

void	add_back(t_list_ps **head, t_list_ps *new)
{
	t_list_ps	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
