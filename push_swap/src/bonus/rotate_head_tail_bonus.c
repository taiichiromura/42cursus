/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_head_tail_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:23:12 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 12:34:21 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

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
	rotate_head_tail(a);
}

void	rb(t_list_ps **b)
{
	rotate_head_tail(b);
}

void	rr(t_list_ps **a, t_list_ps **b)
{
	rotate_head_tail(a);
	rotate_head_tail(b);
}
