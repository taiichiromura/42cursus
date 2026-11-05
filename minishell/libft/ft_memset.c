/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:22:59 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/06 19:58:54 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	value;

	i = 0;
	ptr = (unsigned char *)s;
	value = (unsigned char)c;
	while (i < n)
	{
		ptr[i] = value;
		i++;
	}
	return (s);
}
// #include <stdio.h>

// int	main(void)
// {
// 	char	str[10] = "supreme";
// 	char	c;

// 	c = 'A';
// 	ft_memset(str, c, sizeof(str));
// 	for (size_t i = 0; i < sizeof(str); i++)
// 		printf("%c ", str[i]);
// 	return (0);
// }
