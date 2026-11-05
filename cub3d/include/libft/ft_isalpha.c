/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:28:12 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:35:39 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c < 0 || c > 127)
		return (0);
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (1024);
	else
		return (0);
}
/*

#include <ctype.h>
#include <stdio.h>
#include <assert.h>
int main() {
//	printf("Testing 0: ft_isalpha(0) = %d, isalpha(0) = %d\n",
	ft_isalpha(2147483647), isalpha(2147483647));
	printf("Testing 0: ft_isalpha(0) = %d", ft_isalpha(2147483647));
	assert(ft_isalpha('a') == isalpha('a'));
	assert(ft_isalpha('b') == isalpha('b'));

	assert(ft_isalpha('1') == isalpha('1'));

	printf("All assertions passed.\n");
	return 0;
}
*/
