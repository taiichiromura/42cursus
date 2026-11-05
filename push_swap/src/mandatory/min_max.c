/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:41:35 by tmura             #+#    #+#             */
/*   Updated: 2025/07/10 13:55:20 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	min_num(t_list_ps *node)
{
	int	min_num;

	min_num = INT_MAX;
	while (node)
	{
		if (node->value < min_num)
			min_num = node->value;
		node = node->next;
	}
	return (min_num);
}

int	max_num(t_list_ps *node)
{
	int	max;

	if (!node)
		return (INT_MIN);
	max = node->value;
	while (node)
	{
		if (node->value > max)
			max = node->value;
		node = node->next;
	}
	return (max);
}

int	max(int left, int right)
{
	if (left >= right)
		return (left);
	else
		return (right);
}

int	min(int left, int right)
{
	if (left <= right)
		return (left);
	else
		return (right);
}

int	min4(int a, int b, int c, int d)
{
	if (min(a, b) <= min(c, d))
		return (min(a, b));
	else
		return (min(c, d));
}
