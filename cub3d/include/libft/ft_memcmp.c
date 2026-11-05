/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:42:41 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:43:19 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ss1;
	const unsigned char	*ss2;
	size_t				i;

	i = 0;
	ss1 = (const unsigned char *)s1;
	ss2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
int main(void)
{
    char s1[] = "Hello, World!";
    char s2[] = "Hello, World!";
    char s3[] = "Hello, world!";
    char s4[] = "Hello, Wor";
    char s5[] = "Hello, World!!";

    printf("Test 1: Identical strings\n");
    printf("ft_memcmp: %d, memcmp: %d\n",
	 ft_memcmp(s1, s2, 13), memcmp(s1, s2, 13));

    printf("\nTest 2: Different case\n");
    printf("ft_memcmp: %d, memcmp: %d\n",
	 ft_memcmp(s1, s3, 13), memcmp(s1, s3, 13));

    printf("\nTest 4: Partial match (first 6 characters match)\n");
    printf("ft_memcmp: %d, memcmp: %d\n",
	ft_memcmp(s1, s4, 6), memcmp(s1, s4, 6));

    printf("\nTest 5: Different data at the end\n");
    printf("ft_memcmp: %d, memcmp: %d\n",
	ft_memcmp(s1, s5, 13), memcmp(s1, s5, 13));

    return 0;
}
*/
