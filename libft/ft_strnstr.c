/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:43:54 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:48:15 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	li;
	size_t	little_len;
	char	*big_tmp;

	i = 0;
	big_tmp = (char *)big;
	little_len = ft_strlen(little);
	if (!big && len == 0)
		return (NULL);
	if (little_len == 0 || big == little)
		return (big_tmp);
	while (big_tmp[i] != '\0' && i < len)
	{
		li = 0;
		while (big_tmp[i + li] != '\0' && little[li] != '\0'
			&& big_tmp[i + li] == little[li] && i + li < len)
			li++;
		if (li == little_len)
			return (big_tmp + i);
		i++;
	}
	return (0);
}
