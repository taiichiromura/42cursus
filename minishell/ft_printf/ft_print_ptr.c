/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:57:34 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/14 20:57:18 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptr_count(uintptr_t num)
{
	int	count;

	count = 0;
	while (num != 0)
	{
		count++;
		num = num / 16;
	}
	return (count);
}

void	ft_put_ptr(uintptr_t num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar(num + '0');
		else
			ft_putchar(num - 10 + 'a');
	}
}

int	ft_print_ptr(void *ptr)
{
	int	print_count;

	print_count = 0;
	if (ptr == 0 || ptr == NULL)
		print_count += write(1, "(nil)", 5);
	else
	{
		print_count += write(1, "0x", 2);
		ft_put_ptr((uintptr_t)ptr);
		print_count += ft_ptr_count((uintptr_t)ptr);
	}
	return (print_count);
}
