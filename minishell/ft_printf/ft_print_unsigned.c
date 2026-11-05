/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:31:07 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/13 21:27:54 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_num_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char	*ft_unsigned_itoa(unsigned int num)
{
	int		num_len;
	char	*res;

	num_len = ft_num_len(num);
	res = (char *)malloc(sizeof(char) * (num_len + 1));
	if (!res)
		return (0);
	res[num_len] = '\0';
	while (num_len)
	{
		res[num_len - 1] = num % 10 + '0';
		num = num / 10;
		num_len--;
	}
	return (res);
}

int	ft_print_unsigned(unsigned int n)
{
	int		print_count;
	char	*num;

	print_count = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		print_count++;
	}
	else
	{
		num = ft_unsigned_itoa(n);
		print_count += ft_putstr(num);
		free(num);
	}
	return (print_count);
}
