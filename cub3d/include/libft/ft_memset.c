/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:42:50 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:44:45 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		tmp[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <string.h>
#include <stdio.h>

int main() {
	unsigned char buffer1[10];
    unsigned char buffer2[10];

    // bufferを初期化
    memset(buffer1, 'A', sizeof(buffer1));
    memset(buffer2, 'A', sizeof(buffer2));

    // テスト①：普通に0埋め
    ft_memset(buffer1, 3, 5);
    memset(buffer2, 3, 5);


    if (memcmp(buffer1, buffer2, 10) == 0)
	{
        printf("Test 1 passed!\n");
	}
	else
    {
	  	printf("Test 1 failed!\n");
	}
	return (0);
}
*/
