/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:41:46 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/06 18:55:32 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
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

// 	test1 = '\n';
// 	test2 = 'a';
// 	result = ft_isprint(test1);
// 	printf("%d\n", result);
// 	result = ft_isprint(test2);
// 	printf("%d\n", result);
// 	return (0);
// }
