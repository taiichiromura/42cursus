/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:29:03 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/06 20:37:56 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;

	d = (unsigned char *)dest;
	s = (unsigned const char *)src;
	if (d == s || n == 0)
		return (dest);
	if (s > d)
	{
		while (n--)
		{
			*d = *s;
			d++;
			s++;
		}
	}
	else if (s < d)
	{
		while (n--)
			d[n] = s[n];
	}
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	src[10] = "supreme";
// 	char	dest[10] = "42tokyo";
// 	size_t	size;

// 	size = 8;
// 	ft_memmove(dest, src, size);
// 	printf("%s\n", dest);
// 	return (0);
// }
