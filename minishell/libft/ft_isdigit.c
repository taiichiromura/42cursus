/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:07:13 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/05 19:23:01 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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

// 	test1 = '1';
// 	test2 = 'a';
// 	result = ft_isdigit(test1);
// 	printf("%d\n", result);
// 	result = ft_isdigit(test2);
// 	printf("%d\n", result);
// 	return (0);
// }
