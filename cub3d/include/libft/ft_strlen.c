/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:43:46 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:52:47 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
/*
#include <string.h>
#include <stdio.h>
int main() {
	printf("%zu\n",strlen("ABC"));
	printf("%zu\n",strlen(""));
	printf("%zu\n",ft_strlen("ABC"));
	printf("%zu\n",ft_strlen(""));
	return (0);
}
*/
