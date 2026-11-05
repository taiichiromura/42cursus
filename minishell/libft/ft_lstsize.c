/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:12:39 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/07 16:49:15 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;
// 	int		size;

// 	node1 = ft_lstnew("First");
// 	node2 = ft_lstnew("Second");
// 	node3 = ft_lstnew("Third");
// 	node1->next = node2;
// 	node2->next = node3;
// 	size = ft_lstsize(node1);
// 	printf("リストのノード数: %d\n", size);
// 	return (0);
// }
