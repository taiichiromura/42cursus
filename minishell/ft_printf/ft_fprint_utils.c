/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprint_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:46:19 by ktakeru           #+#    #+#             */
/*   Updated: 2025/08/19 18:24:54 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_fd_int(char *s, int fd)
{
	int	len;

	if (!s)
		return (write(fd, "(null)", 6));
	len = ft_strlen(s);
	write(fd, s, len);
	return (len);
}

int	ft_putchar_fd_int(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putnbr_fd_int(long n, int fd)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += ft_putchar_fd_int('-', fd);
		n *= -1;
	}
	if (n >= 10)
		count += ft_putnbr_fd_int(n / 10, fd);
	count += ft_putchar_fd_int(n % 10 + '0', fd);
	return (count);
}

int	ft_puthex_fd(unsigned int n, int fd, char case_type)
{
	char	*base;
	int		count;

	count = 0;
	if (case_type == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n >= 16)
		count += ft_puthex_fd(n / 16, fd, case_type);
	count += ft_putchar_fd_int(base[n % 16], fd);
	return (count);
}

int	ft_putptr_fd(void *ptr, int fd)
{
	unsigned long long	n;
	char				*base;
	int					count;

	if (!ptr)
		return (ft_putstr_fd_int("(nil)", fd));
	n = (unsigned long long)ptr;
	base = "0123456789abcdef";
	count = 0;
	count += ft_putstr_fd_int("0x", fd);
	if (n >= 16)
		count += ft_putptr_fd((void *)(n / 16), fd);
	count += ft_putchar_fd_int(base[n % 16], fd);
	return (count);
}
