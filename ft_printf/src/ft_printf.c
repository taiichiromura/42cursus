/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:49:12 by tmura             #+#    #+#             */
/*   Updated: 2025/06/01 11:03:54 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		total_len;

	if (!s)
		return (ERROR);
	va_start(ap, s);
	total_len = handle_format_loop(s, &ap);
	va_end(ap);
	if (total_len == ERROR)
		return (ERROR);
	return (total_len);
}

int	handle_format_loop(const char *s, va_list *ap)
{
	int	i;
	int	total_len;
	int	result_handle_percent;

	i = 0;
	total_len = 0;
	result_handle_percent = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			result_handle_percent = handle_percent(s, &i, ap);
			if (result_handle_percent == ERROR)
				return (ERROR);
			total_len += result_handle_percent;
		}
		else
		{
			if (safe_write(1, &s[i], 1) == ERROR)
				return (ERROR);
			total_len++;
			i++;
		}
	}
	return (total_len);
}

int	handle_percent(const char *s, int *i, va_list *ap)
{
	t_format	fmt;
	int			len;

	(*i)++;
	ft_bzero(&fmt, sizeof(t_format));
	if (scan_line(s, i, ap, &fmt) == ERROR)
		return (ERROR);
	len = print_arg(&fmt, ap);
	if (len == ERROR)
		return (ERROR);
	return (len);
}

int	print_arg(t_format *fmt, va_list *ap)
{
	if (fmt->specifier == 'c')
		return (print_char(fmt, va_arg(*ap, int)));
	else if (fmt->specifier == 's')
		return (print_string(fmt, va_arg(*ap, char *)));
	else if (fmt->specifier == 'd' || fmt->specifier == 'i')
		return (print_decimal(fmt, va_arg(*ap, int)));
	else if (fmt->specifier == 'u')
		return (print_unsigned_decimal(fmt, va_arg(*ap, unsigned int)));
	else if (fmt->specifier == 'x')
		return (print_hexadecimal_low(fmt, va_arg(*ap, unsigned int)));
	else if (fmt->specifier == 'X')
		return (print_hexadecimal_up(fmt, va_arg(*ap, unsigned int)));
	else if (fmt->specifier == 'p')
		return (print_pointer(fmt, va_arg(*ap, void *)));
	else if (fmt->specifier == '%')
		return (print_percent());
	return (ERROR);
}
