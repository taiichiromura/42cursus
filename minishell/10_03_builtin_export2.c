/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_03_builtin_export2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:18:18 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/02 20:23:42 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_varname(const char *key)
{
	if (!key || *key == '\0')
		return (0);
	if (!(*key >= 'a' && *key <= 'z') && !(*key >= 'A' && *key <= 'Z')
		&& *key != '_')
		return (0);
	key++;
	while (*key)
	{
		if (!(*key >= 'a' && *key <= 'z') && !(*key >= 'A' && *key <= 'Z')
			&& !(*key >= '0' && *key <= '9') && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

static int	handle_export_key_value(char *arg, char *eq_sign,
		t_env_var **env_list)
{
	char	*key;
	char	*value;
	int		status;

	key = ft_strndup(arg, eq_sign - arg);
	if (!key)
	{
		perror("bash: export: ft_strndup failed");
		return (1);
	}
	if (!is_valid_varname(key))
	{
		ft_fprintf(STDERR_FILENO,
			"bash: export: `%s': not a valid identifier\n", key);
		free(key);
		return (1);
	}
	value = eq_sign + 1;
	status = set_env_var(env_list, key, value, 1);
	free(key);
	return (status);
}

int	handle_export_arg(char *arg, t_env_var **env_list)
{
	char	*eq_sign;

	eq_sign = ft_strchr(arg, '=');
	if (!eq_sign)
	{
		if (is_valid_varname(arg))
		{
			if (set_env_var(env_list, arg, NULL, 1) != 0)
				return (1);
			return (0);
		}
		ft_fprintf(STDERR_FILENO,
			"bash: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	else
	{
		return (handle_export_key_value(arg, eq_sign, env_list));
	}
}
