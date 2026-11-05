/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:37:06 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/19 18:18:55 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_conversion(const char c, va_list args)
{
	int	print_count;

	print_count = 0;
	if (c == 'c')
		print_count += ft_putchar(va_arg(args, int));
	else if (c == 's')
		print_count += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		print_count += ft_print_ptr(va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		print_count += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		print_count += ft_print_unsigned(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		print_count += ft_print_hex(va_arg(args, unsigned int), c);
	else if (c == '%')
		print_count += ft_putchar('%');
	else
		return (-1);
	return (print_count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		temp_count;
	int		count;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	temp_count = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			temp_count = handle_conversion(*(++format), args);
			if (temp_count < 0)
				return (va_end(args), -1);
			count += temp_count;
		}
		else
			count += ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (count);
}
