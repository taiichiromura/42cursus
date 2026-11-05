/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:43:49 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:47:49 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*processed_s;

	if (!s || !f)
		return (NULL);
	i = 0;
	processed_s = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!processed_s)
		return (NULL);
	while (s[i])
	{
		processed_s[i] = f(i, s[i]);
		i++;
	}
	processed_s[i] = '\0';
	return (processed_s);
}
/*
#include <stdio.h>

int main(void)
{

	char *result = ft_strmapi("suzumenooyado", to_upper);
	if (result)
	{
		printf("%s\n", result); // 出力: SUZUMENOOYADO
		free(result);
	}
}
*/
