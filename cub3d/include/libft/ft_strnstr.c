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
/*
#include <string.h>
#include <stdio.h>
#include <stddef.h>
int main(void)
{
    char big[] = "Hello, World!";
    char little[] = "World";
    char little2[] = "world";  // 大文字小文字の違い
    char little3[] = "llo";
    char little5[] = "";  // 空文字列
    size_t len = 13;

    // Test 1: littleがbigに存在する
    printf("Test 1: littleがbigに存在する\n");
    printf("ft_strnstr: %s\n", ft_strnstr(big, little, len));
    printf("strnstr: %s\n\n", strnstr(big, little, len));

    // Test 2: littleがbigに存在しない
    printf("Test 2: littleがbigに存在しない\n");
    printf("ft_strnstr: %s\n", ft_strnstr(big, little2, len));
    printf("strnstr: %s\n\n", strnstr(big, little2, len));

    // Test 3: littleが空文字列の場合
    printf("Test 3: littleが空文字列の場合\n");
    printf("ft_strnstr: %s\n", ft_strnstr(big, little5, len));
    printf("strnstr: %s\n\n", strnstr(big, little5, len));

    // Test 4: lenがlittleの長さより小さい場合
    printf("Test 4: lenがlittleの長さより小さい場合\n");
    printf("ft_strnstr: %s\n", ft_strnstr(big, little, 4));
    printf("strnstr: %s\n\n", strnstr(big, little, 4));

    // Test 5: lenがbigの長さより大きい場合
    printf("Test 5: lenがbigの長さより大きい場合\n");
    printf("ft_strnstr: %s\n", ft_strnstr(big, little, 100));
    printf("strnstr: %s\n\n", strnstr(big, little, 100));

    // Test 6: lenがexact matchの場合
    printf("Test 6: lenがexact matchの場合\n");
    printf("ft_strnstr: %s\n", ft_strnstr(big, little3, len));
    printf("strnstr: %s\n\n", strnstr(big, little3, len));

    return 0;
}
*/
