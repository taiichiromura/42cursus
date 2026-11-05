/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:08:46 by tmura             #+#    #+#             */
/*   Updated: 2025/08/22 19:29:19 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strv(char **v)
{
	int	i;

	if (!v)
		return ;
	i = 0;
	while (v[i])
	{
		free(v[i]);
		i++;
	}
	free(v);
}

void	free_args_partial(char **args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(args[i]);
		i++;
	}
}

int	grow_args(char ***dst, int *cap, int argc)
{
	char	**newv;
	int		i;

	*cap *= 2;
	newv = (char **)malloc(sizeof(char *) * (*cap));
	if (!newv)
		return (0);
	i = 0;
	while (i < argc)
	{
		newv[i] = (*dst)[i];
		i++;
	}
	free(*dst);
	*dst = newv;
	return (1);
}

int	append_plain(t_command *cmd, char *val, int *argc, int *cap)
{
	char	*s;

	if (*argc + 1 >= *cap)
		if (!grow_args(&cmd->args, cap, *argc))
			return (0);
	s = ft_strdup(val);
	if (!s)
		return (0);
	cmd->args[*argc] = s;
	(*argc)++;
	return (1);
}

int	append_wildcard(t_command *cmd, char *val, int *argc, int *cap)
{
	char	**exp;
	int		i;
	char	*s;

	exp = expand_wildcard_token(val);
	if (!exp)
		return (0);
	i = 0;
	while (exp[i])
	{
		if (*argc + 1 >= *cap)
			if (!grow_args(&cmd->args, cap, *argc))
				return (free_strv(exp), 0);
		s = ft_strdup(exp[i]);
		if (!s)
			return (free_strv(exp), 0);
		cmd->args[*argc] = s;
		(*argc)++;
		i++;
	}
	free_strv(exp);
	return (1);
}
