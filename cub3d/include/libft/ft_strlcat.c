/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:43:40 by tmura             #+#    #+#             */
/*   Updated: 2025/05/07 14:59:06 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	dst_len = 0;
	src_len = ft_strlen(src);
	while (dst[dst_len] && dst_len < size)
		dst_len++;
	if (dst_len == size)
		return (size + src_len);
	i = 0;
	while (src[i] && dst_len + i + 1 < size)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if (dst_len + i < size)
		dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/*

#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	dest[20] = "rrrrrr";  // 初期値6文字 + 空き領域あり
	const char *src = "lorem ipsum dolor sit amet";
	size_t	size = 15;
	size_t	result;

	// テスト実行
	result = ft_strlcat(dest, src, size);

	// 結果出力
	printf("Return value: %zu\n", result); // 期待値: 6 + strlen(src) = 6 + 26 = 32
	printf("Dest buffer : ");
	for (size_t i = 0; i < size; i++)
	{
		if (dest[i] == '\0')
			printf("^@");
		else
			putchar(dest[i]);
	}
	printf("\n");

	return (0);
}
*/
