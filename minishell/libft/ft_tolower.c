/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:24:24 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/05 19:25:53 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	test;
// 	int	res;

// 	test = 'A';
// 	res = ft_tolower(test);
// 	printf("%c\n", res);
// 	return (0);
// }
