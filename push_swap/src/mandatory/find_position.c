/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_position.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:43:36 by tmura             #+#    #+#             */
/*   Updated: 2025/07/10 13:54:24 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	find_max_position(t_list_ps *stack_b, int max)
{
	int			pos;
	t_list_ps	*tmp;

	pos = 0;
	tmp = stack_b;
	while (tmp)
	{
		if (tmp->value == max)
			return (pos + 1);
		pos++;
		tmp = tmp->next;
	}
	return (0);
}

int	find_position_b(t_list_ps *stack_a, t_list_ps *stack_b)
{
	int			val;
	int			min;
	int			max;
	int			pos;
	t_list_ps	*tmp;

	val = stack_a->value;
	min = min_num(stack_b);
	max = max_num(stack_b);
	if (val > max || val < min)
		return (find_max_position(stack_b, max));
	tmp = stack_b;
	pos = 0;
	while (tmp && tmp->next)
	{
		if (tmp->value < val && val < tmp->next->value)
			return (pos + 1);
		pos++;
		tmp = tmp->next;
	}
	return (0);
}

void	rotate_a_to_max(t_list_ps **stack_b)
{
	int			max;
	int			pos;
	int			size;
	t_list_ps	*tmp;

	max = max_num(*stack_b);
	pos = 0;
	tmp = *stack_b;
	while (tmp && tmp->value != max)
	{
		tmp = tmp->next;
		pos++;
	}
	size = count_lists(*stack_b);
	if (pos <= size / 2)
		while ((*stack_b)->value != max)
			rb(stack_b);
	else
		while ((*stack_b)->value != max)
			rrb(stack_b);
}

void	execute_move(t_list_ps **stack_a, t_list_ps **stack_b, t_cheap mv)
{
	t_rot	rot;

	rot.na = count_lists(*stack_b);
	rot.nb = count_lists(*stack_a);
	rot.rra_a = rot.na - mv.ra;
	rot.rrb_b = rot.nb - mv.rb;
	execute_pattern(stack_a, stack_b, mv, rot);
	pa(stack_b, stack_a);
}
