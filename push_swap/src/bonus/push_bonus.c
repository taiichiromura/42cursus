/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:23:54 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 12:34:19 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

void	pa(t_list_ps **a, t_list_ps **b)
{
	t_list_ps	*node;

	if (!b || !*b)
		return ;
	node = *b;
	*b = node->next;
	node->next = *a;
	*a = node;
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
}
