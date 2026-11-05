/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:19:04 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/07 15:35:10 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	how_many_letters(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*convert_to_char(char *res, unsigned int number, int len)
{
	while (number > 0)
	{
		res[len] = 48 + (number % 10);
		len--;
		number = number / 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				len;
	unsigned int	number;

	len = how_many_letters(n);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = '\0';
	len--;
	if (n == 0)
	{
		res[0] = '0';
		return (res);
	}
	if (n <= 0)
	{
		number = n * -1;
		res[0] = '-';
	}
	else
		number = n;
	res = convert_to_char(res, number, len);
	return (res);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int		n;
// 	char	*res;

// 	n = 123;
// 	res = ft_itoa(n);
// 	printf("%s\n", res);
// 	free(res);
// 	return (0);
// }
