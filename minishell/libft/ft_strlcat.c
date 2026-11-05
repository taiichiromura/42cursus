/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:48:02 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/05 19:25:05 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = 0;
	while (src[srclen] != '\0')
		srclen++;
	dstlen = 0;
	while (dst[dstlen] != '\0' && dstlen < size)
		dstlen++;
	if (dstlen == size)
		return (srclen + dstlen);
	i = 0;
	while (i < srclen && dstlen + i < size - 1)
	{
		dst[i + dstlen] = src[i];
		i++;
	}
	dst[i + dstlen] = '\0';
	return (srclen + dstlen);
}
// #include <stdio.h>

// int	main(void)
// {
// 	char	src[10] = " is love";
// 	char	dst[20] = "supreme";
// 	size_t	size;
// 	size_t	res;

// 	size = 20;
// 	res = ft_strlcat(dst, src, size);
// 	printf("%s\n", dst);
// 	printf("%zu\n", res);
// 	return (0);
// }
