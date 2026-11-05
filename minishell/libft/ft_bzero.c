/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:26:24 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/06 20:01:20 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
// #include <stdio.h>

// int	main(void)
// {
// 	char	str[8];

// 	ft_bzero(str, sizeof(str));
// 	for (size_t i = 0; sizeof(str) > i; i++)
// 		printf("%d ", str[i]);
// 	printf("\n");
// 	return (0);
// }
