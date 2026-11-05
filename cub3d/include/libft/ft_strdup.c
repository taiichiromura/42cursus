/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:43:26 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:46:22 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s1) + 1;
	ptr = malloc(sizeof(char) * len);
	if (!ptr)
		return (0);
	ptr = ft_memcpy(ptr, s1, len);
	return (ptr);
}
/*
#include <string.h>
#include <stdio.h>
#include <assert.h>
int	main(void)
{
	const char *src = "Hello, 42Tokyo!";
	char *copy = ft_strdup(src);

	// NULLでないか確認
	assert(copy != NULL);

	// 内容が一致しているか
	assert(strcmp(copy, src) == 0);

	// アドレスが違う（deep copyされてる）か
	assert(copy != src);

	printf("All ft_strdup tests passed ✅\n");

	free(copy);
	return 0;
}
*/
