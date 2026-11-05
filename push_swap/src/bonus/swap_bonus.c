/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:24:24 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 12:34:30 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

int	swap_top_two_nodes(t_list_ps **node)
{
	t_list_ps	*head;
	t_list_ps	*second;

	if (!node || !*node || !(*node)->next)
		return (0);
	head = *node;
	second = (*node)->next;
	head->next = second->next;
	second->next = head;
	*node = second;
	return (1);
}

void	sa(t_list_ps **a)
{
	swap_top_two_nodes(a);
}

void	sb(t_list_ps **b)
{
	swap_top_two_nodes(b);
}

void	ss(t_list_ps **a, t_list_ps **b)
{
	swap_top_two_nodes(a);
	swap_top_two_nodes(b);
}
