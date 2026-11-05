/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:30:47 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/05 19:22:54 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
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

// 	test1 = 1000;
// 	test2 = '=';
// 	result = ft_isascii(test1);
// 	printf("%d\n", result);
// 	result = ft_isascii(test2);
// 	printf("%d\n", result);
// 	return (0);
// }
