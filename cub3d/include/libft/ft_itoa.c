/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:41:58 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:39:02 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_numlen(int n, long *num)
{
	int	len;

	*num = (long)n;
	if (n <= 0)
		len = 1;
	else
		len = 0;
	if (*num < 0)
		*num = -*num;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	num;
	int		len;
	char	*str;

	len = ft_numlen(n, &num);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[0] = '-';
	while (num > 0)
	{
		str[--len] = '0' + (num % 10);
		num /= 10;
	}
	return (str);
}

/*
#include <string.h>
#include <stdio.h>

int main(void)
{
	int values[] = {0, 42, -1234, 2147483647, -2147483648};
	for (int i = 0; i < 5; i++)
	{
		char *s = ft_itoa(values[i]);
		printf("%d → %s\n", values[i], s);
		free(s);
	}
	return 0;
}
*/
