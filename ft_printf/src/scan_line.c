/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:49:39 by tmura             #+#    #+#             */
/*   Updated: 2025/06/01 11:20:36 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	scan_line(const char *line, int *i, va_list *ap, t_format *fmt)
{
	parse_flags(line, i, fmt);
	parse_width(line, i, ap, fmt);
	parse_precision(line, i, ap, fmt);
	if (parse_specifier(line, i, fmt) == ERROR)
		return (ERROR);
	return (OK);
}

void	parse_flags(const char *line, int *i, t_format *fmt)
{
	while (1)
	{
		if (line[*i] == '-')
			fmt->flg |= FLG_LEFT;
		else if (line[*i] == '0')
			fmt->flg |= FLG_ZERO;
		else if (line[*i] == '+')
			fmt->flg |= FLG_PLUS;
		else if (line[*i] == ' ')
			fmt->flg |= FLG_SPACE;
		else if (line[*i] == '#')
			fmt->flg |= FLG_HASH;
		else
			break ;
		(*i)++;
	}
}

void	parse_width(const char *s, int *i, va_list *ap, t_format *fmt)
{
	if (s[*i] == '*')
	{
		fmt->width = va_arg(*ap, int);
		(*i)++;
	}
	else if (ft_isdigit(s[*i]))
	{
		fmt->width = ft_atoi(&s[*i]);
		while (ft_isdigit(s[*i]))
			(*i)++;
	}
	if (fmt->width < 0)
	{
		fmt->flg |= FLG_LEFT;
		fmt->width = -(fmt->width);
	}
}

void	parse_precision(const char *s, int *i, va_list *ap, t_format *fmt)
{
	if (s[*i] && s[*i] == '.')
	{
		fmt->has_precision = 1;
		(*i)++;
		if (s[*i] && s[*i] == '*')
		{
			fmt->precision = va_arg(*ap, int);
			(*i)++;
		}
		else if (s[*i] && ft_isdigit(s[*i]))
		{
			fmt->precision = ft_atoi(&s[*i]);
			while (ft_isdigit(s[*i]))
				(*i)++;
		}
		else
			fmt->precision = 0;
	}
}

int	parse_specifier(const char *line, int *i, t_format *fmt)
{
	if (line[*i] == 'c')
		fmt->specifier = 'c';
	else if (line[*i] == 's')
		fmt->specifier = 's';
	else if (line[*i] == 'p')
		fmt->specifier = 'p';
	else if (line[*i] == 'd')
		fmt->specifier = 'd';
	else if (line[*i] == 'i')
		fmt->specifier = 'i';
	else if (line[*i] == 'u')
		fmt->specifier = 'u';
	else if (line[*i] == 'x')
		fmt->specifier = 'x';
	else if (line[*i] == 'X')
		fmt->specifier = 'X';
	else if (line[*i] == '%')
		fmt->specifier = '%';
	else
		return (ERROR);
	(*i)++;
	return (OK);
}
