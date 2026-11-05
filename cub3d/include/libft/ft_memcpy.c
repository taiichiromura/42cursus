/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:42:35 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 22:20:58 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp;	

	i = 0;
	if (!dest && !src)
		return (NULL);
	tmp = (unsigned char *)dest;
	while (i < n)
	{
		tmp[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
	unsigned char buffer1[10] = {1, 2, 3, 4, 5, 0}; // テスト用データ
	unsigned char buffer2[10] = {0};
    ft_memcpy(((void*)0), ((void*)0), 3);
 
	ft_memcpy(buffer2, buffer1, 4);
  
	if (memcmp(buffer1, buffer2, 4) == 0)
	{
		printf("Test passed!\n");
	}
	else
	{
		printf("Test failed!\n");
	}
	return 0;
}
*/
