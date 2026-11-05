/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:54:15 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/05 19:23:26 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*strs1 = s1;
	const unsigned char	*strs2 = s2;

	while (n--)
	{
		if (*strs1 != *strs2)
			return (*strs1 - *strs2);
		strs1++;
		strs2++;
	}
	return (0);
}
// #include <stdio.h>

// int	main(void)
// {
// 	char		strs1[10] = "supreme";
// 	char		strs2[10] = "tupreme";
// 	size_t		size;
// 	long int	res;

// 	size = 7;
// 	res = ft_memcmp(strs1, strs2, size);
// 	printf("%ld\n", res);
// 	return (0);
// }
