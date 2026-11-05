/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:46:12 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/05 19:24:47 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*arr;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (s[size] != '\0')
		size++;
	arr = (char *)malloc((size + 1) * sizeof(char));
	if (arr == 0)
		return (NULL);
	while (s[i] != '\0')
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
// #include <stdio.h>

// int	main(void)
// {
// 	char	strs[10] = "supreme";
// 	char	*res;

// 	res = ft_strdup(strs);
// 	printf("%s\n", res);
// 	free(res);
// 	return (0);
// }
