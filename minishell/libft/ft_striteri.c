/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:23:49 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/06 20:55:09 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// void	change(unsigned int i, char *s)
// {
// 	if (i % 2 == 0)
// 	{
// 		if (*s >= 'a' && *s <= 'z')
// 			*s = *s - 32;
// 	}
// }
// #include <stdio.h>

// int	main(void)
// {
// 	char	strs[20] = "Supreme is love";

// 	ft_striteri(strs, change);
// 	printf("%s\n", strs);
// 	return (0);
// }
