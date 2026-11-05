/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_lis_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:31:33 by tmura             #+#    #+#             */
/*   Updated: 2025/07/10 13:31:34 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	mark_lis_nodes(t_list_ps *stack_a)
{
	t_mark	mark;

	mark.indexes = find_lis_indexes(stack_a, &(mark.len));
	if (!mark.indexes)
		return ;
	mark.tmp = stack_a;
	mark.i = 0;
	set_keep_flags(&mark);
	free(mark.indexes);
}

void	set_keep_flags(t_mark *mark)
{
	while (mark->tmp)
	{
		mark->tmp->keep = 0;
		mark->j = 0;
		while (mark->j < mark->len)
		{
			if (mark->i == mark->indexes[mark->j])
			{
				mark->tmp->keep = 1;
				break ;
			}
			mark->j++;
		}
		mark->tmp = mark->tmp->next;
		mark->i++;
	}
}

void	initialize_arrays(int *lengths, int *prev, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		lengths[i] = 1;
		prev[i] = -1;
		i++;
	}
}

void	copy_list_to_array(t_list_ps *stack_a, int *arr)
{
	int			i;
	t_list_ps	*tmp;

	i = 0;
	tmp = stack_a;
	while (tmp)
	{
		arr[i] = tmp->value;
		tmp = tmp->next;
		i++;
	}
}

int	*find_lis_indexes(t_list_ps *stack_a, int *lis_len)
{
	t_lis_data	list_data;
	int			*lis_indexes;

	list_data.size = count_lists(stack_a);
	list_data.arr = malloc(sizeof(int) * list_data.size);
	list_data.lengths = malloc(sizeof(int) * list_data.size);
	list_data.prev = malloc(sizeof(int) * list_data.size);
	if (!list_data.arr || !list_data.lengths || !list_data.prev)
		return (free(list_data.arr), free(list_data.lengths),
			free(list_data.prev), NULL);
	copy_list_to_array(stack_a, list_data.arr);
	initialize_arrays(list_data.lengths, list_data.prev, list_data.size);
	list_data.max_end = find_lis_dp(list_data.arr,
			list_data.lengths, list_data.prev, list_data.size);
	*lis_len = list_data.lengths[list_data.max_end];
	lis_indexes = build_lis_indexes(list_data.prev,
			*lis_len, list_data.max_end);
	free(list_data.arr);
	free(list_data.lengths);
	free(list_data.prev);
	return (lis_indexes);
}
