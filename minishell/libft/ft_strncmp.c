/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:41:03 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/06 21:23:25 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 0 && *s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	s1[10] = "supreme";
// 	char	s2[10] = "surprise";
// 	size_t	size;
// 	int		res;

// 	size = 5;
// 	res = ft_strncmp(s1, s2, size);
// 	printf("%d\n", res);
// 	return (0);
// }
