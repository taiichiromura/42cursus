/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pattern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:47:47 by tmura             #+#    #+#             */
/*   Updated: 2025/07/10 13:52:43 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	exec_pat_1(t_list_ps **stack_a, t_list_ps **stack_b, t_cheap mv)
{
	int	i;
	int	m;

	m = min(mv.ra, mv.rb);
	i = 0;
	while (i < m)
	{
		rr(stack_a, stack_b);
		i++;
	}
	while (i < mv.ra)
	{
		ra(stack_b);
		i++;
	}
	i = m;
	while (i < mv.rb)
	{
		rb(stack_a);
		i++;
	}
}

void	exec_pat_2(t_list_ps **stack_a, t_list_ps **stack_b,
			int rra_a, int rrb_b)
{
	int	i;
	int	m;

	m = min(rra_a, rrb_b);
	i = 0;
	while (i < m)
	{
		rrr(stack_a, stack_b);
		i++;
	}
	while (i < rra_a)
	{
		rra(stack_b);
		i++;
	}
	i = m;
	while (i < rrb_b)
	{
		rrb(stack_a);
		i++;
	}
}

void	exec_pat_3(t_list_ps **stack_a, t_list_ps **stack_b,
			t_cheap mv, int rrb_b)
{
	int	i;

	i = 0;
	while (i < mv.ra)
	{
		ra(stack_b);
		i++;
	}
	i = 0;
	while (i < rrb_b)
	{
		rrb(stack_a);
		i++;
	}
}

void	exec_pat_4(t_list_ps **stack_a, t_list_ps **stack_b,
			int rra_a, t_cheap mv)
{
	int	i;

	i = 0;
	while (i < rra_a)
	{
		rra(stack_b);
		i++;
	}
	i = 0;
	while (i < mv.rb)
	{
		rb(stack_a);
		i++;
	}
}

void	execute_pattern(
		t_list_ps **stack_a, t_list_ps **stack_b,
			t_cheap mv, t_rot rot)
{
	if (mv.pat == 1)
		exec_pat_1(stack_a, stack_b, mv);
	else if (mv.pat == 2)
		exec_pat_2(stack_a, stack_b, rot.rra_a, rot.rrb_b);
	else if (mv.pat == 3)
		exec_pat_3(stack_a, stack_b, mv, rot.rrb_b);
	else if (mv.pat == 4)
		exec_pat_4(stack_a, stack_b, rot.rra_a, mv);
}
