/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:55:59 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 11:20:39 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	check_sign(char *str, long *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	return (sign);
}

int	validate_digits(char *str, int i)
{
	if (!ft_isdigit(str[i]))
	{
		return (ERROR);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			return (ERROR);
		}
		i++;
	}
	return (OK);
}

long	safe_atoi(char *str, t_list_ps **a)
{
	long	i;
	long	nbr;
	int		sign;

	i = 0;
	nbr = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = check_sign(str, &i);
	if (validate_digits(str, i) == ERROR)
		error_exit(a);
	while (ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + (str[i++] - '0');
		if ((sign == 1 && nbr > INT_MAX) || (sign == -1 && -(nbr) < INT_MIN))
			error_exit(a);
	}
	return (nbr * sign);
}
