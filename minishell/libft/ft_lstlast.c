/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:12:55 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/07 18:52:22 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;
// 	t_list	*last;

// 	node1 = ft_lstnew("First");
// 	node2 = ft_lstnew("Second");
// 	node3 = ft_lstnew("Third");
// 	node1->next = node2;
// 	node2->next = node3;
// 	last = ft_lstlast(node1);
// 	if (last)
// 		printf("最後のノード: %s\n", (char *)last->content);
// 	else
// 		printf("リストが空です\n");
// 	return (0);
// }
