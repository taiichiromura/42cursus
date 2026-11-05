/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_05_builtin_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:23:06 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/18 16:39:02 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_atoll_preprocess(const char **str, int *sign)
{
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
		(*str)++;
	*sign = 1;
	if (**str == '-')
	{
		*sign = -1;
		(*str)++;
	}
	else if (**str == '+')
	{
		(*str)++;
	}
	if (!('0' <= **str && **str <= '9'))
		return (2);
	return (0);
}

static int	ft_atoll_convert(const char **str, long long *num, int sign)
{
	*num = 0;
	while ('0' <= **str && **str <= '9')
	{
		if (sign == 1)
		{
			if (*num > LLONG_MAX / 10 || (*num == LLONG_MAX / 10 && **str
					- '0' > LLONG_MAX % 10))
			{
				*num = LLONG_MAX;
				return (1);
			}
		}
		else
		{
			if (*num < LLONG_MIN / 10 || (*num == LLONG_MIN / 10 && **str
					- '0' > -(LLONG_MIN % 10)))
			{
				*num = LLONG_MIN;
				return (1);
			}
		}
		*num = *num * 10 + sign * (**str - '0');
		(*str)++;
	}
	return (0);
}

int	ft_atoll(const char *str, long long *res, char **endptr)
{
	int			sign;
	long long	num;
	int			status;
	const char	*original_str = str;

	status = ft_atoll_preprocess(&str, &sign);
	if (status != 0)
	{
		if (endptr)
			*endptr = (char *)original_str;
		return (status);
	}
	status = ft_atoll_convert(&str, &num, sign);
	if (status != 0)
	{
		if (endptr)
			*endptr = (char *)str;
		return (status);
	}
	*res = num;
	if (endptr)
		*endptr = (char *)str;
	if (*str != '\0')
		return (2);
	return (0);
}

long long	check_exit_args(char **args, long long *exit_code_ptr,
		t_shell_context *context)
{
	char	*endptr;
	int		atoll_status;

	atoll_status = ft_atoll(args[1], exit_code_ptr, &endptr);
	if (atoll_status == 1 || atoll_status == 2)
	{
		ft_fprintf(STDERR_FILENO,
			"bash: exit: %s: "
			"numeric argument required\n",
			args[1]);
		context->last_exit_status = 2;
		return (-1);
	}
	if (args[2])
	{
		ft_fprintf(STDERR_FILENO, "bash: exit: too many arguments\n");
		return (1);
	}
	return (0);
}

int	builtin_exit(char **args, t_shell_context *context)
{
	long long	exit_code;
	int			ret_val;

	if (args[1])
	{
		ret_val = check_exit_args(args, &exit_code, context);
		if (ret_val == -1)
			exit(context->last_exit_status);
		if (ret_val == 1)
			return (1);
		if (ret_val != 0)
		{
			context->last_exit_status = ret_val;
			exit(context->last_exit_status);
		}
		context->last_exit_status = (int)(exit_code % 256);
		if (context->last_exit_status < 0)
		{
			context->last_exit_status += 256;
		}
		exit(context->last_exit_status);
	}
	else
		exit(context->last_exit_status);
	return (0);
}
