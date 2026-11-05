/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:29:58 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:36:54 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (2048);
	else
		return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int main(void) {
	printf("%d\n",ft_isdigit(2147483647));
	//printf("%d\n",isdigit('8'));
	//printf("%d", ft_isdigit('1'));
}
*/
