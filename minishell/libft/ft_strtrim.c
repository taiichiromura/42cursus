/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:50:07 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/07 15:40:15 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	included_or_not(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*arr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (included_or_not(s1[start], set) == 1)
		start++;
	end = ft_strlen(s1);
	while ((included_or_not(s1[end - 1], set) == 1) && end > start)
		end--;
	arr = (char *)malloc((end - start + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		arr[i] = s1[start];
		start++;
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
// #include <stdio.h>

// int	main(void)
// {
// 	char	strs[50] = "I will graduate from 42 by next April hopefully";
// 	char	set[10] = "hopefully";
// 	char	*res;

// 	res = ft_strtrim(strs, set);
// 	printf("%s\n", res);
// 	free(res);
// 	return (0);
// }
