/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:49:23 by tmura             #+#    #+#             */
/*   Updated: 2025/05/30 10:49:11 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	write_nums(t_format *fmt, t_info *info)
{
	if (fmt->flg & FLG_LEFT)
	{
		if (write_left(info) == ERROR)
			return (ERROR);
	}
	else
	{
		if (write_right(info, fmt) == ERROR)
			return (ERROR);
	}
	return (OK);
}

int	write_right_zero(t_info *info)
{
	if (info->sign_char)
		if (safe_write(1, &info->sign_char, 1) == ERROR)
			return (ERROR);
	if (info->prefix_flg == 1)
		if (safe_write(1, "0x", 2) == ERROR)
			return (ERROR);
	if (info->prefix_flg == 2)
		if (safe_write(1, "0X", 2) == ERROR)
			return (ERROR);
	while (info->padding-- > 0)
		if (safe_write(1, "0", 1) == ERROR)
			return (ERROR);
	while (info->precision_padding-- > 0)
		if (safe_write(1, "0", 1) == ERROR)
			return (ERROR);
	if (info->char_num && info->len > 0)
		if (safe_write(1, info->char_num, info->len) == ERROR)
			return (ERROR);
	return (OK);
}

int	write_right_not_zero(t_info *info)
{
	while (info->padding-- > 0)
		if (safe_write(1, " ", 1) == ERROR)
			return (ERROR);
	if (info->sign_char)
		if (safe_write(1, &info->sign_char, 1) == ERROR)
			return (ERROR);
	if (info->prefix_flg == 1)
		if (safe_write(1, "0x", 2) == ERROR)
			return (ERROR);
	if (info->prefix_flg == 2)
		if (safe_write(1, "0X", 2) == ERROR)
			return (ERROR);
	while (info->precision_padding-- > 0)
		if (safe_write(1, "0", 1) == ERROR)
			return (ERROR);
	if (info->char_num && info->len > 0)
		if (safe_write(1, info->char_num, info->len) == ERROR)
			return (ERROR);
	return (OK);
}

int	write_right(t_info *info, t_format *fmt)
{
	if (fmt->flg & FLG_ZERO && !fmt->has_precision)
		return (write_right_zero(info));
	else
		return (write_right_not_zero(info));
}

int	write_left(t_info *info)
{
	if (info->sign_char)
		if (safe_write(1, &info->sign_char, 1) == ERROR)
			return (ERROR);
	if (info->prefix_flg == 1)
		if (safe_write(1, "0x", 2) == ERROR)
			return (ERROR);
	if (info->prefix_flg == 2)
		if (safe_write(1, "0X", 2) == ERROR)
			return (ERROR);
	while (info->precision_padding-- > 0)
		if (safe_write(1, "0", 1) == ERROR)
			return (ERROR);
	if (info->char_num && info->len > 0)
		if (safe_write(1, info->char_num, info->len) == ERROR)
			return (ERROR);
	while (info->padding-- > 0)
		if (safe_write(1, " ", 1) == ERROR)
			return (ERROR);
	return (OK);
}
