/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_to_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:48:19 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 12:24:29 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	rotate_a_to_min(t_list_ps **stack_a)
{
	int	min;
	int	pos;
	int	size;

	min = min_num(*stack_a);
	pos = find_min_position(*stack_a, min);
	size = count_lists(*stack_a);
	if (pos <= size / 2)
	{
		while ((*stack_a)->value != min)
			ra(stack_a);
	}
	else
	{
		while ((*stack_a)->value != min)
			rra(stack_a);
	}
}

int	find_min_position(t_list_ps *stack_a, int min)
{
	int			pos;
	t_list_ps	*tmp;

	pos = 0;
	tmp = stack_a;
	while (tmp->value != min)
	{
		tmp = tmp->next;
		pos++;
	}
	return (pos);
}

int	find_over_max_position(t_list_ps *stack_a, int max)
{
	int			pos;
	int			size;
	t_list_ps	*tmp;

	pos = 0;
	tmp = stack_a;
	while (tmp->value != max)
	{
		tmp = tmp->next;
		pos++;
	}
	size = count_lists(stack_a);
	return ((pos + 1) % size);
}

int	find_position_a(int val, t_list_ps *stack_a)
{
	int			min;
	int			max;
	int			pos;
	t_list_ps	*tmp;

	min = min_num(stack_a);
	max = max_num(stack_a);
	if (val < min)
		return (find_min_position(stack_a, min));
	if (val > max)
		return (find_over_max_position(stack_a, max));
	tmp = stack_a;
	pos = 0;
	while (tmp->next)
	{
		if (tmp->value < val && val < tmp->next->value)
			return (pos + 1);
		tmp = tmp->next;
		pos++;
	}
	return (0);
}

void	push_back_to_a(t_list_ps **stack_a, t_list_ps **stack_b)
{
	int	val;
	int	pos_a;
	int	size_a;

	while (*stack_b)
	{
		val = (*stack_b)->value;
		pos_a = find_position_a(val, *stack_a);
		size_a = count_lists(*stack_a);
		if (pos_a <= size_a / 2)
		{
			while (pos_a-- > 0)
				ra(stack_a);
		}
		else
		{
			pos_a = size_a - pos_a;
			while (pos_a-- > 0)
				rra(stack_a);
		}
		pa(stack_a, stack_b);
	}
}
