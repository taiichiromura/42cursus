/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:31:25 by tmura             #+#    #+#             */
/*   Updated: 2025/07/10 13:31:27 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	find_lis_dp(int *arr, int *lengths, int *prev, int size)
{
	int		i;
	int		max_len;
	int		max_end;

	max_len = 1;
	max_end = 0;
	i = 1;
	while (i < size)
	{
		if (update_lis(arr, lengths, prev, i) > max_len)
		{
			max_len = lengths[i];
			max_end = i;
		}
		i++;
	}
	return (max_end);
}

int	*build_lis_indexes(int *prev, int lis_len, int max_end)
{
	int		*indexes;
	int		k;
	int		i;

	indexes = malloc(sizeof(int) * lis_len);
	if (!indexes)
		return (NULL);
	k = max_end;
	i = lis_len - 1;
	while (i >= 0)
	{
		indexes[i] = k;
		k = prev[k];
		i--;
	}
	return (indexes);
}

int	update_lis(int *arr, int *lengths, int *prev, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		if (arr[j] < arr[i] && lengths[j] + 1 > lengths[i])
		{
			lengths[i] = lengths[j] + 1;
			prev[i] = j;
		}
		j++;
	}
	return (lengths[i]);
}
