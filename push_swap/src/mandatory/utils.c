/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:28:24 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 12:25:59 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_list_ps	*parse_args(int argc, char **argv)
{
	t_list_ps	*a;
	t_list_ps	*node;
	int			i;
	long		val;

	a = NULL;
	i = 1;
	while (i < argc)
	{
		val = safe_atoi(argv[i], &a);
		if (is_duplicate((int)val, a))
			error_exit(&a);
		node = new_node(val);
		if (!node)
			error_exit(&a);
		add_back(&a, node);
		i++;
	}
	return (a);
}

int	is_duplicate(int val, t_list_ps *stack)
{
	while (stack)
	{
		if (stack->value == val)
			return (1);
		stack = stack->next;
	}
	return (0);
}

void	free_stack(t_list_ps **stack)
{
	t_list_ps	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

int	is_sorted(t_list_ps *a)
{
	while (a && a->next)
	{
		if (a->value > a->next->value)
			return (0);
		a = a->next;
	}
	return (OK);
}

int	count_lists(t_list_ps *nodes)
{
	int	count;

	count = 0;
	while (nodes)
	{
		count++;
		nodes = nodes->next;
	}
	return (count);
}
