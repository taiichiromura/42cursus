/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:46:19 by ktakeru           #+#    #+#             */
/*   Updated: 2025/08/19 18:24:00 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	handle_format_specifier(int fd, const char **format, va_list ap)
{
	int	count;

	count = 0;
	if (**format == 's')
		count = ft_putstr_fd_int(va_arg(ap, char *), fd);
	else if (**format == 'c')
		count = ft_putchar_fd_int(va_arg(ap, int), fd);
	else if (**format == 'd' || **format == 'i')
		count = ft_putnbr_fd_int(va_arg(ap, int), fd);
	else if (**format == 'x')
		count = ft_puthex_fd(va_arg(ap, unsigned int), fd, 'x');
	else if (**format == 'p')
		count = ft_putptr_fd(va_arg(ap, void *), fd);
	else if (**format == '%')
		count = ft_putchar_fd_int('%', fd);
	return (count);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += handle_format_specifier(fd, &format, ap);
		}
		else
		{
			write(fd, format, 1);
			count++;
		}
		format++;
	}
	va_end(ap);
	return (count);
}
