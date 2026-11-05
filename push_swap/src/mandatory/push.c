/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:23:54 by tmura             #+#    #+#             */
/*   Updated: 2025/07/10 10:23:56 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	pa(t_list_ps **a, t_list_ps **b)
{
	t_list_ps	*node;

	if (!b || !*b)
		return ;
	node = *b;
	*b = node->next;
	node->next = *a;
	*a = node;
	write(1, "pa\n", 3);
}

void	pb(t_list_ps **a, t_list_ps **b)
{
	t_list_ps	*node;

	if (!a || !*a)
		return ;
	node = *a;
	*a = node->next;
	node->next = *b;
	*b = node;
	write(1, "pb\n", 3);
}
