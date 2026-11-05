/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:40:17 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 12:25:18 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	sort_three(t_list_ps **a, int f, int s, int t)
{
	if (f < s && s < t)
		return (1);
	if (f > s && s < t && f < t)
		sa(a);
	else if (f > s && s > t)
	{
		sa(a);
		rra(a);
	}
	else if (f > s && s < t && f > t)
		ra(a);
	else if (f < s && s > t && f < t)
	{
		sa(a);
		ra(a);
	}
	else if (f < s && s > t && f > t)
		rra(a);
	return (3);
}

int	sort_two(t_list_ps **a)
{
	if ((*a)->value > (*a)->next->value)
		sa(a);
	return (2);
}

int	sort_two_or_three(t_list_ps **a)
{
	int	len;
	int	f;
	int	s;
	int	t;

	len = count_lists(*a);
	if (len < 2)
		return (1);
	if (len == 2)
		return (sort_two(a));
	f = (*a)->value;
	s = (*a)->next->value;
	t = (*a)->next->next->value;
	return (sort_three(a, f, s, t));
}

void	push_min(t_list_ps **a, t_list_ps **b)
{
	int			min;
	int			size;
	int			i;
	t_list_ps	*tmp;

	min = min_num(*a);
	size = count_lists(*a);
	tmp = *a;
	i = 0;
	while (tmp && tmp->value != min)
	{
		tmp = tmp->next;
		i++;
	}
	if (i <= size / 2)
	{
		while ((*a)->value != min)
			ra(a);
	}
	else
	{
		while ((*a)->value != min)
			rra(a);
	}
	pb(a, b);
}

void	sort_five_or_less(t_list_ps **a, t_list_ps **b)
{
	if (count_lists(*a) <= 3)
	{
		sort_two_or_three(a);
		return ;
	}
	push_min(a, b);
	if (count_lists(*a) > 3)
		push_min(a, b);
	sort_two_or_three(a);
	while (count_lists(*b))
	{
		pa(a, b);
		if ((*a)->value > max_num(*a))
			ra(a);
	}
	rotate_a_to_min(a);
}
