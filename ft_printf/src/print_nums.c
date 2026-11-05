/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nums.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:49:28 by tmura             #+#    #+#             */
/*   Updated: 2025/06/01 12:11:42 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_decimal(t_format *fmt, int decimal)
{
	t_info	info;

	ft_bzero(&info, sizeof(t_info));
	if (format_sign(&info, fmt, decimal) == ERROR)
		return (free(info.char_num), ERROR);
	if (write_nums(fmt, &info) == ERROR)
		return (free(info.char_num), ERROR);
	free(info.char_num);
	return (info.total_len);
}

int	print_unsigned_decimal(t_format *fmt, unsigned int decimal)
{
	t_info	info;

	ft_bzero(&info, sizeof(t_info));
	if (format_unsign(&info, fmt, decimal, "0123456789") == ERROR)
		return (free(info.char_num), ERROR);
	if (write_nums(fmt, &info) == ERROR)
		return (free(info.char_num), ERROR);
	free(info.char_num);
	return (info.total_len);
}

int	print_hexadecimal_low(t_format *fmt, unsigned int hex_decimal_low)
{
	int			low;
	t_info		info;

	low = 1;
	ft_bzero(&info, sizeof(t_info));
	if ((fmt->flg & FLG_HASH) && hex_decimal_low != 0)
		info.prefix_flg = low;
	if (format_unsign(&info, fmt, hex_decimal_low, "0123456789abcdef") == ERROR)
		return (free(info.char_num), ERROR);
	if (write_nums(fmt, &info) == ERROR)
		return (free(info.char_num), ERROR);
	free(info.char_num);
	return (info.total_len);
}

int	print_hexadecimal_up(t_format *fmt, unsigned int hex_decimal_up)
{
	int			up;
	t_info		info;

	up = 2;
	ft_bzero(&info, sizeof(t_info));
	if ((fmt->flg & FLG_HASH) && hex_decimal_up != 0)
		info.prefix_flg = up;
	if (format_unsign(&info, fmt, hex_decimal_up, "0123456789ABCDEF") == ERROR)
		return (free(info.char_num), ERROR);
	if (write_nums(fmt, &info) == ERROR)
		return (free(info.char_num), ERROR);
	free(info.char_num);
	return (info.total_len);
}

int	print_pointer(t_format *fmt, void *ptr)
{
	unsigned long long	ptr_num;
	t_info				info;

	ptr_num = (unsigned long long)ptr;
	if (ptr_num == 0)
	{
		print_string(fmt, "(nil)");
		return (5);
	}
	ft_bzero(&info, sizeof(t_info));
	if (fmt->has_precision)
		fmt->has_precision = 0;
	info.prefix_flg = 1;
	if (format_unsign(&info, fmt, ptr_num, "0123456789abcdef") == ERROR)
		return (free(info.char_num), ERROR);
	if (write_nums(fmt, &info) == ERROR)
		return (free(info.char_num), ERROR);
	free(info.char_num);
	return (info.total_len);
}
