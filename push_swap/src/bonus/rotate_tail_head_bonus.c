/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_tail_head_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:21:22 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 12:34:25 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

int	rotate_tail_head(t_list_ps **node)
{
	t_list_ps	*tail;
	t_list_ps	*head;
	t_list_ps	*prev;

	if (!node || !*node || !(*node)->next)
		return (0);
	head = *node;
	tail = *node;
	prev = NULL;
	while (tail->next)
	{
		prev = tail;
		tail = tail->next;
	}
	prev->next = NULL;
	tail->next = head;
	*node = tail;
	return (1);
}

void	rra(t_list_ps **a)
{
	rotate_tail_head(a);
}

void	rrb(t_list_ps **b)
{
	rotate_tail_head(b);
}

void	rrr(t_list_ps **a, t_list_ps **b)
{
	rotate_tail_head(a);
	rotate_tail_head(b);
}
