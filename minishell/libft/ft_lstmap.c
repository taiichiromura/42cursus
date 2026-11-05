/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:35:37 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/08 14:36:10 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*content;

	new_lst = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		content = f(lst->content);
		if (!content)
			return (ft_lstclear(&new_lst, del), NULL);
		new_node = ft_lstnew(content);
		if (!new_node)
			return (del(content), ft_lstclear(&new_lst, del), NULL);
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}

// void	*to_uppercase(void *content)
// {
// 	char	*str;
// 	char	*new_str;
// 	int		i;

// 	str = (char *)content;
// 	new_str = ft_strdup(str);
// 	if (!new_str)
// 		return (NULL);
// 	i = 0;
// 	while (new_str[i])
// 	{
// 		new_str[i] = ft_toupper(new_str[i]);
// 		i++;
// 	}
// 	return (new_str);
// }

// void	free_content(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*new_lst;
// 	t_list	*node;

// 	lst = ft_lstnew(ft_strdup("hello"));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("world")));
// 	new_lst = ft_lstmap(lst, &to_uppercase, &free_content);
// 	node = new_lst;
// 	while (node)
// 	{
// 		printf("%s\n", (char *)node->content);
// 		node = node->next;
// 	}
// 	ft_lstclear(&lst, &free_content);
// 	ft_lstclear(&new_lst, &free_content);
// 	return (0);
// }
