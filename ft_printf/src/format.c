/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:49:06 by tmura             #+#    #+#             */
/*   Updated: 2025/06/01 12:10:23 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	max(int left, int right)
{
	if (left >= right)
		return (left);
	else
		return (right);
}

char	sign_check(t_format *fmt, int num)
{
	if (num < 0)
		return ('-');
	if (fmt->flg & FLG_PLUS)
		return ('+');
	if (fmt->flg & FLG_SPACE)
		return (' ');
	else
		return ('\0');
}

int	format_sign(t_info *info, t_format *fmt, int num)
{
	const char	*ten_base;

	ten_base = "0123456789";
	info->sign_char = '\0';
	info->sign_char = sign_check(fmt, num);
	info->sign_len = (info->sign_char != '\0');
	if (num < 0)
		num = -num;
	info->char_num = itoa_base(num, ten_base);
	if (!info->char_num)
		return (ERROR);
	info->len = ft_strlen(info->char_num);
	if (fmt->has_precision && fmt->precision == 0 && num == 0)
		info->len = 0;
	if (fmt->precision > info->len)
		info->precision_padding = fmt->precision - info->len;
	info->total_len = info->sign_len + info->precision_padding + info->len;
	info->padding = max(fmt->width - info->total_len, 0);
	info->total_len += info->padding;
	return (OK);
}

int	format_unsign(t_info *info, t_format *fmt,
						unsigned long long num, char *base)
{
	if (info->prefix_flg)
		info->has_prefix = 2;
	info->char_num = itoa_base_unsigned(num, base);
	if (!info->char_num)
		return (ERROR);
	info->len = ft_strlen(info->char_num);
	if (fmt->has_precision && fmt->precision == 0 && num == 0)
		info->len = 0;
	if (fmt->precision > info->len)
		info->precision_padding = fmt->precision - info->len;
	info->total_len = info->precision_padding + info->len + info->has_prefix;
	info->padding = max(fmt->width - info->total_len, 0);
	info->total_len += info->padding;
	return (OK);
}

void	format_string(t_info *info, t_format *fmt, char *string)
{
	if (!string)
		info->char_num = "(null)";
	else
		info->char_num = string;
	info->len = ft_strlen(info->char_num);
	if (fmt->has_precision && fmt->precision < info->len)
		info->len = fmt->precision;
	if (fmt->has_precision && fmt->precision == 0)
		info->len = 0;
	if (!string && fmt->has_precision && fmt->precision <= 5)
		info->len = 0;
	info->padding = max(fmt->width - info->len, 0);
}
