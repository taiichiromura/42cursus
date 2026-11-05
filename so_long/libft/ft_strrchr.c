/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:43:57 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:48:21 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*ptr;
	unsigned char	ch;

	i = 0;
	ptr = 0;
	ch = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == ch)
			ptr = (char *)(s + i);
		i++;
	}
	if (s[i] == ch)
		ptr = (char *)(s + i);
	return (ptr);
}
