/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_unmarked_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:41:53 by tmura             #+#    #+#             */
/*   Updated: 2025/07/10 13:41:56 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	push_unmarked_nodes(t_list_ps **a, t_list_ps **b)
{
	while (exists_unmarked(*a))
	{
		if ((*a)->keep == 0)
			pb(a, b);
		else
			ra(a);
	}
	rotate_a_to_min(a);
}

int	exists_unmarked(t_list_ps *a)
{
	while (a)
	{
		if (a->keep == 0)
			return (1);
		a = a->next;
	}
	return (0);
}
