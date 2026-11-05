/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 00:41:21 by tmura             #+#    #+#             */
/*   Updated: 2025/07/11 16:41:39 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	sort_b_into_a(t_list_ps **b, t_list_ps **a)
{
	t_cheap	mv;

	while (count_lists(*b))
	{
		mv = calculate(*b, *a);
		execute_move(b, a, mv);
	}
}

void	start_sort(t_list_ps **a, t_list_ps **b)
{
	if (count_lists(*a) <= 5)
	{
		sort_five_or_less(a, b);
		return ;
	}
	mark_lis_nodes(*a);
	push_unmarked_nodes(a, b);
	sort_b_into_a(b, a);
	rotate_a_to_min(a);
}

int	main(int argc, char **argv)
{
	t_list_ps	*a;
	t_list_ps	*b;

	a = parse_args(argc, argv);
	b = NULL;
	if (!a)
		return (1);
	if (!is_sorted(a))
		start_sort(&a, &b);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
