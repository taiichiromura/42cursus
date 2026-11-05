/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:43:43 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:05:24 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
int main(void)
{
	//const char src[] = "hello world";
	//char dst1[20];
	char dst2[20];

	// Test 1: 正常コピー
	//size_t result_std = strlcpy(NULL, "", 0);
	size_t result_ft  = ft_strlcpy(NULL, "", 0);

	printf("Test 1: Normal copy\n");
	//printf("Expected   : %s (%zu)\n", dst1, result_std);
	printf("ft_strlcpy : %s (%zu)\n\n", dst2, result_ft);

	// Test 2: 切り詰めコピー
	char dst3[5];
	char dst4[5];

	result_std = strlcpy(dst3, src, sizeof(dst3));
	result_ft  = ft_strlcpy(dst4, src, sizeof(dst4));

	printf("Test 2: Truncated copy (dstsize = 5)\n");
	printf("Expected   : %s (%zu)\n", dst3, result_std);
	printf("ft_strlcpy : %s (%zu)\n\n", dst4, result_ft);

	// Test 3: dstsize = 0
	char dst5[1];
	char dst6[1];

	result_std = strlcpy(dst5, src, 0);
	result_ft  = ft_strlcpy(dst6, src, 0);

	printf("Test 3: dstsize = 0\n");
	printf("Expected   : (%zu)\n", result_std);
	printf("ft_strlcpy : (%zu)\n\n", result_ft);

	return 0;
}

*/
