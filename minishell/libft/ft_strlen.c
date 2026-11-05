/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:00:12 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/06 21:34:45 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int		result;
// 	char	*test1;
// 	char	*test2;

// 	test1 = "supreme";
// 	test2 = "888";
// 	result = ft_strlen(test1);
// 	printf("%d\n", result);
// 	result = ft_strlen(test2);
// 	printf("%d\n", result);
// 	return (0);
// }
