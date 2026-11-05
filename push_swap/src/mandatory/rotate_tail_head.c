/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_tail_head.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:21:22 by tmura             #+#    #+#             */
/*   Updated: 2025/07/10 11:11:17 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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
	if (rotate_tail_head(a))
	{
		write(1, "rra\n", 4);
	}
}

void	rrb(t_list_ps **b)
{
	if (rotate_tail_head(b))
	{
		write(1, "rrb\n", 4);
	}
}

void	rrr(t_list_ps **a, t_list_ps **b)
{
	int	is_rotated_a;
	int	is_rotated_b;

	is_rotated_a = rotate_tail_head(a);
	is_rotated_b = rotate_tail_head(b);
	if (is_rotated_a || is_rotated_b)
	{
		write(1, "rrr\n", 4);
	}
}
