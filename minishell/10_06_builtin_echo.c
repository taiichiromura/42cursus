/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_06_builtin_echo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:09:58 by ktakeru           #+#    #+#             */
/*   Updated: 2025/08/28 19:15:20 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_option_str(const char *s)
{
	if (!s || ft_strncmp(s, "-n", 2) != 0)
		return (0);
	s += 2;
	while (*s && *s == 'n')
		s++;
	return (*s == '\0');
}

static void	echo_option_handle(char **args, int *has_n_option, int *i)
{
	int	start_index;

	start_index = 1;
	while (args[start_index] && is_n_option_str(args[start_index]))
	{
		*has_n_option = 1;
		start_index++;
	}
	*i = start_index;
}

int	builtin_echo(char **args)
{
	int	i;
	int	has_n_option;

	i = 1;
	has_n_option = 0;
	echo_option_handle(args, &has_n_option, &i);
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!has_n_option)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
