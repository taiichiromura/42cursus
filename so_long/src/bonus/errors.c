/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:30 by tmura             #+#    #+#             */
/*   Updated: 2025/07/18 12:21:31 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	error_exit(const char *error_massages)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, error_massages, ft_strlen(error_massages));
	exit(1);
}

void	error(const char *error_massages)
{
	write(STDERR_FILENO, error_massages, ft_strlen(error_massages));
}
