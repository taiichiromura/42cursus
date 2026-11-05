/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_02_external_cmd_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:44:31 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/03 16:09:07 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_and_check_path(char *start, char *end, char *cmd)
{
	char	*dir;
	char	*full_path;

	dir = (char *)malloc(end - start + 1);
	if (!dir)
		return (NULL);
	ft_strncpy(dir, start, end - start);
	dir[end - start] = '\0';
	full_path = join_path(dir, cmd);
	if (!full_path)
	{
		free(dir);
		return (NULL);
	}
	if (access(full_path, X_OK) == 0)
	{
		free(dir);
		return (full_path);
	}
	free(dir);
	free(full_path);
	return (NULL);
}

static char	*check_path_list(char *path_env, char *cmd)
{
	char	*start;
	char	*end;
	char	*result_path;

	start = path_env;
	while (*start)
	{
		end = ft_strchr(start, ':');
		if (!end)
			end = start + ft_strlen(start);
		result_path = extract_and_check_path(start, end, cmd);
		if (result_path)
			return (result_path);
		if (*end == ':')
			start = end + 1;
		else
			break ;
	}
	return (NULL);
}

static int	check_direct_path(char *cmd, char **cmd_path)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			*cmd_path = ft_strdup(cmd);
			return (0);
		}
		return (126);
	}
	return (127);
}

static int	ft_find_path(char *cmd, t_env_var *env_list, char **cmd_path)
{
	char	*path_env;
	char	*path;

	if (ft_strchr(cmd, '/'))
		return (check_direct_path(cmd, cmd_path));
	path_env = my_getenv_val(env_list, "PATH");
	if (!path_env)
	{
		*cmd_path = ft_strjoin("./", cmd);
		return (0);
	}
	path = check_path_list(path_env, cmd);
	if (path)
		return ((*cmd_path = path), 0);
	return (127);
}

int	find_command_path(char *cmd, t_env_var *env_list, char **cmd_path)
{
	*cmd_path = NULL;
	if (!cmd || ft_strlen(cmd) == 0)
	{
		return (127);
	}
	return (ft_find_path(cmd, env_list, cmd_path));
}
