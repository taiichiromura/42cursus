/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:55:39 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/05 19:25:32 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			last = s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)last);
}
// #include <stdio.h>

// int	main(void)
// {
// 	const char	strs[20] = "supreme";
// 	int			str;
// 	char		*res;

// 	str = 'p';
// 	res = ft_strrchr(strs, str);
// 	printf("%s\n", res);
// 	return (0);
// }
