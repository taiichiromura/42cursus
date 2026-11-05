/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:49:47 by tmura             #+#    #+#             */
/*   Updated: 2025/05/30 10:49:48 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	safe_write(int fd, const void *buf, size_t count)
{
	if (write(fd, buf, count) == ERROR)
		return (ERROR);
	return (OK);
}
