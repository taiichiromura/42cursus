/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:43:23 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:46:07 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == ch)
		return ((char *)s + i);
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
int main(void)
{
    const char *s = "Hello World";
	//ASSERT_EQ_STR(ft_strrchr(s, 'l' + 256), strrchr(s, 'l' + 256));

    printf("Original strchr: %s\n", strchr(s, 'l' + 256));
    printf("Your ft_strchr : %s\n", ft_strchr(s, 'l' + 256));

    printf("Original strchr: %s\n", strchr(s, '\0'));
    printf("Your ft_strchr : %s\n", ft_strchr(s, '\0'));

    printf("Original strchr: %s\n", strchr(s, 'o'));
    printf("Your ft_strchr : %s\n", ft_strchr(s, 'o'));

    return 0;
}
*/
