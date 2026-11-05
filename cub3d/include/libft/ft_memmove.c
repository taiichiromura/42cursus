/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:42:45 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 22:20:13 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		while (n--)
		{
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
		}
	}
	else
	{
		while (n--)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
/*
int main()
{
	unsigned char buffer1[10] = {1, 2, 3, 4, 5, 0};
	unsigned char buffer2[10] = {0};

	ft_memmove(buffer2, buffer1, 4); // 修正

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
