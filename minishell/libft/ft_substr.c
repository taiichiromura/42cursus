/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:26:56 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/06 22:19:25 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	i;
	size_t	len_s;
	size_t	sub_len;

	if (!s)
		return (0);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	sub_len = len_s - start;
	if (sub_len > len)
		sub_len = len;
	arr = (char *)malloc((sub_len + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < sub_len)
	{
		arr[i] = s[start + i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
// #include <stdio.h>

// int	main(void)
// {
// 	char			strs[10] = "supreme";
// 	unsigned int	start;
// 	size_t			len;
// 	char			*res;

// 	start = 4;
// 	len = 10;
// 	res = ft_substr(strs, start, len);
// 	printf("%s\n", res);
// 	return (0);
// }
