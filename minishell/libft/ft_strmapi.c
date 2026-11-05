/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:49:57 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/07 15:41:03 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	int				s_len;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	res = (char *)malloc((s_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

// char	capital(unsigned int i, char c)
// {
// 	if (i % 2 == 0)
// 	{
// 		if (c >= 'a' && c <= 'z')
// 			c = c - 32;
// 	}
// 	return (c);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	char	strs[50] = "I wanna go home now";
// 	char	*res;

// 	res = ft_strmapi(strs, capital);
// 	printf("%s\n", res);
// 	free(res);
// 	return (0);
// }
