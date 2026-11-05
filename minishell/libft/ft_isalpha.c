/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:57:09 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/05 19:22:48 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	test1;
// 	int	test2;
// 	int	result;

// 	test1 = 10000;
// 	test2 = 'a';
// 	result = ft_isalpha(test1);
// 	printf("%d\n", result);
// 	result = ft_isalpha(test2);
// 	printf("%d\n", result);
// 	return (0);
// }
