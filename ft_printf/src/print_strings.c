/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:49:26 by tmura             #+#    #+#             */
/*   Updated: 2025/06/01 11:55:34 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_width(t_format *fmt)
{
	int	i;

	i = 0;
	while (i < fmt->width - 1)
	{
		if (safe_write(1, " ", 1) == ERROR)
			return (ERROR);
		i++;
	}
	return (i);
}

int	print_char(t_format *fmt, const char c)
{
	int	print_size;

	print_size = 1;
	if (fmt->flg & FLG_LEFT)
	{
		if (safe_write(1, &c, 1) == ERROR)
			return (ERROR);
		print_size += print_width(fmt);
	}
	else
	{
		print_size += print_width(fmt);
		if (safe_write(1, &c, 1) == ERROR)
			return (ERROR);
	}
	return (print_size);
}

int	write_string(t_format *fmt, t_info *info)
{
	if (fmt->flg & FLG_LEFT)
	{
		if (write_left(info) == ERROR)
			return (ERROR);
	}
	else
	{
		if (write_right_not_zero(info) == ERROR)
			return (ERROR);
	}
	return (OK);
}

int	print_string(t_format *fmt, char *string)
{
	int			actual_padding;
	t_info		info;

	actual_padding = 0;
	ft_bzero(&info, sizeof(t_info));
	if (!string)
		info.char_num = "(null)";
	else
		info.char_num = string;
	info.len = ft_strlen(info.char_num);
	if (fmt->has_precision && fmt->precision < info.len)
		info.len = fmt->precision;
	if (fmt->has_precision && fmt->precision == 0)
		info.len = 0;
	if (!string && fmt->has_precision && fmt->precision <= 5)
		info.len = 0;
	actual_padding = max(fmt->width - info.len, 0);
	info.padding = actual_padding;
	if (write_string(fmt, &info) == ERROR)
		return (ERROR);
	return (info.len + actual_padding);
}

int	print_percent(void)
{
	char	percent;

	percent = '%';
	if (safe_write(1, &percent, 1) == ERROR)
		return (ERROR);
	return (1);
}
