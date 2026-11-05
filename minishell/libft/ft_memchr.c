/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:53:31 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/05 19:23:17 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*strs;

	strs = s;
	while (n--)
	{
		if (*strs == (unsigned char)c)
			return ((void *)strs);
		strs++;
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	strs[20] = "Tea Astro Radio";
// 	int		c;
// 	size_t	size;
// 	void	*res;

// 	c = 's';
// 	size = 10;
// 	res = ft_memchr(strs, c, size);
// 	printf("%ld\n", (char *)res - strs);
// 	return (0);
// }
