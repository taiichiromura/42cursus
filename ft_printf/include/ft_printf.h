/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:49:17 by tmura             #+#    #+#             */
/*   Updated: 2025/06/01 12:23:23 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define FLG_LEFT 2
# define FLG_ZERO 4
# define FLG_PLUS 8
# define FLG_SPACE 16
# define FLG_HASH 32
# define FLAG_DOT 64
# define ERROR -1
# define OK 1

typedef struct s_format
{
	int		flg;
	int		width;
	int		precision;
	int		has_precision;
	char	specifier;
}	t_format;

typedef struct s_info
{
	char	sign_char;
	int		sign_len;
	int		len;
	int		precision_padding;
	int		total_len;
	int		padding;
	char	*char_num;
	int		has_prefix;
	int		prefix_flg;
}	t_info;

int		ft_printf(const char *s, ...);

int		scan_line(const char *line, int *i, va_list *ap, t_format *fmt);
void	parse_flags(const char *line, int *i, t_format *fmt);
void	parse_width(const char *line, int *i, va_list *ap, t_format *fmt);
void	parse_precision(const char *line, int *i, va_list *ap, t_format *fmt);
int		parse_specifier(const char *line, int *i, t_format *fmt);

int		print_arg(t_format *fmt, va_list *ap);
int		print_char(t_format *fmt, const char c);
int		print_string(t_format *fmt, char *s);
int		print_decimal(t_format *fmt, int n);
int		print_unsigned_decimal(t_format *fmt, unsigned int n);
int		print_hexadecimal_low(t_format *fmt, unsigned int n);
int		print_hexadecimal_up(t_format *fmt, unsigned int n);
int		print_pointer(t_format *fmt, void *ptr);
int		print_percent(void);

int		ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_atoi(const char *s);
char	*ft_itoa(int n);
char	*itoa_base(long long n, const char *base);
char	*itoa_base_unsigned(unsigned long long n, const char *base);
int		write_left(t_info *info);
int		write_right(t_info *info, t_format *fmt);
int		write_right_not_zero(t_info *info);
int		write_right_zero(t_info *info);
int		write_nums(t_format *fmt, t_info *info);

int		max(int a, int b);
char	*convert_to_base(unsigned long long n,
			const char *base, int base_len, int digit);
int		count_digits_unsigned(unsigned long long n, int base_len);
void	ft_bzero(void *s, size_t n);
int		format_sign(t_info *info, t_format *fmt, int decimal);
int		format_unsign(t_info *info, t_format *fmt,
			unsigned long long decimal, char *base);
void	format_string(t_info *info, t_format *fmt, char *str);

int		handle_format_loop(const char *s, va_list *ap);
int		handle_percent(const char *s, int *i, va_list *ap);
int		safe_write(int fd, const void *buf, size_t count);

#endif
