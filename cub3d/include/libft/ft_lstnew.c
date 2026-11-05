/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:42:28 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:53:46 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/*
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
	t_list *node = ft_lstnew("Hello");
	if (node)
	{
		printf("Content: %s\n", (char *)node->content);
	}
	else
	{
		printf("Memory allocation failed\n");
	}
	return 0;
}
*/
