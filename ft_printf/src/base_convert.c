/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:48:48 by tmura             #+#    #+#             */
/*   Updated: 2025/06/01 12:08:50 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	count_digits_unsigned(unsigned long long num, int base_len)
{
	int	digit;

	digit = 0;
	if (num == 0)
		digit = 1;
	while (num > 0)
	{
		digit++;
		num /= base_len;
	}
	return (digit);
}

char	*convert_to_base(unsigned long long num,
			const char *base, int base_len, int digit)
{
	char	*converted_num;

	converted_num = malloc(digit + 1);
	if (!converted_num)
		return (NULL);
	converted_num[digit] = '\0';
	if (num == 0)
		converted_num[0] = '0';
	while (digit-- > 0 && num > 0)
	{
		converted_num[digit] = base[num % base_len];
		num /= base_len;
	}
	return (converted_num);
}

char	*itoa_base_unsigned(unsigned long long num, const char *base)
{
	int		base_len;
	int		digit;

	base_len = ft_strlen(base);
	digit = count_digits_unsigned(num, base_len);
	return (convert_to_base(num, base, base_len, digit));
}

char	*itoa_base(long long num, const char *base)
{
	unsigned long long	abs_val;
	int					base_len;
	int					digit;

	if (num < 0)
		abs_val = (unsigned long long)(-(num + 1)) + 1;
	else
		abs_val = (unsigned long long)num;
	base_len = ft_strlen(base);
	digit = count_digits_unsigned(abs_val, base_len);
	return (convert_to_base(abs_val, base, base_len, digit));
}
