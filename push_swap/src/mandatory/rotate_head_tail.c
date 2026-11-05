/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_head_tail.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:23:12 by tmura             #+#    #+#             */
/*   Updated: 2025/07/10 10:25:50 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_list_ps	*ft_lstlast_ps(t_list_ps *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	rotate_head_tail(t_list_ps **node)
{
	t_list_ps	*tail;
	t_list_ps	*head;

	if (!node || !*node || !(*node)->next)
		return (0);
	head = *node;
	*node = head->next;
	head->next = NULL;
	tail = ft_lstlast_ps(*node);
	tail->next = head;
	return (1);
}

void	ra(t_list_ps **a)
{
	if (rotate_head_tail(a))
	{
		write(1, "ra\n", 3);
	}
}

void	rb(t_list_ps **b)
{
	if (rotate_head_tail(b))
	{
		write(1, "rb\n", 3);
	}
}

void	rr(t_list_ps **a, t_list_ps **b)
{
	int	rotate_head_tail_a;
	int	rotate_head_tail_b;

	rotate_head_tail_a = rotate_head_tail(a);
	rotate_head_tail_b = rotate_head_tail(b);
	if (rotate_head_tail_a || rotate_head_tail_b)
	{
		write(1, "rr\n", 3);
	}
}
