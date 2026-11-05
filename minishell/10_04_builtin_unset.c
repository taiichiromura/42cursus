/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_04_builtin_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:52:13 by ktakeru           #+#    #+#             */
/*   Updated: 2025/08/19 18:07:29 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(t_env_var **env_list, const char *key)
{
	t_env_var	*current;
	t_env_var	*prev;

	current = *env_list;
	prev = NULL;
	if (current && ft_strcmp(current->key, key) == 0)
	{
		*env_list = current->next;
		free(current->key);
		free(current->value);
		free(current);
		return ;
	}
	while (current && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		prev->next = current->next;
		free(current->key);
		free(current->value);
		free(current);
	}
}

int	builtin_unset(char **args, t_env_var **env_list)
{
	int	i;
	int	ret_status;

	i = 1;
	ret_status = 0;
	while (args[i])
	{
		if (is_valid_varname(args[i]) != 0)
		{
			remove_env_var(env_list, args[i]);
		}
		i++;
	}
	return (ret_status);
}
