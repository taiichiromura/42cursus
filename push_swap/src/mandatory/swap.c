/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:24:24 by tmura             #+#    #+#             */
/*   Updated: 2025/07/10 11:13:10 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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
	if (swap_top_two_nodes(a))
	{
		write(1, "sa\n", 3);
	}
}

void	sb(t_list_ps **b)
{
	if (swap_top_two_nodes(b))
	{
		write(1, "sb\n", 3);
	}
}

void	ss(t_list_ps **a, t_list_ps **b)
{
	int		success_swap_a;
	int		success_swap_b;

	success_swap_a = swap_top_two_nodes(a);
	success_swap_b = swap_top_two_nodes(b);
	if (success_swap_a || success_swap_b)
	{
		write(1, "ss\n", 3);
	}
}
