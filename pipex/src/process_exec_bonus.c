/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:43:39 by tmura             #+#    #+#             */
/*   Updated: 2025/07/24 14:53:24 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	check_cmd_exist(char **cmd_args)
{
	if (access(cmd_args[0], F_OK) != 0)
	{
		perror(cmd_args[0]);
		free_split(cmd_args);
		exit(127);
	}
	if (access(cmd_args[0], X_OK) != 0)
	{
		perror(cmd_args[0]);
		free_split(cmd_args);
		exit(126);
	}
	return (1);
}

char	*resolve_command(char *arg_cmd, char *cmd_env)
{
	char	**cmd_paths;
	int		i;
	char	*cmd;
	char	*joined_slash;

	cmd_paths = ft_split(cmd_env, ':');
	i = 0;
	while (cmd_paths[i])
	{
		cmd = cmd_paths[i];
		joined_slash = ft_strjoin(cmd, "/");
		cmd = ft_strjoin(joined_slash, arg_cmd);
		free(joined_slash);
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		{
			free_split(cmd_paths);
			return (cmd);
		}
		i++;
		free(cmd);
	}
	free_split(cmd_paths);
	return (NULL);
}

char	*get_cmd_path(char *arg_cmd, char **envp)
{
	int		i;
	char	*cmd_env;

	i = 0;
	cmd_env = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			cmd_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!cmd_env)
		return ("no path");
	return (resolve_command(arg_cmd, cmd_env));
}

void	try_exec_in_pwd(char **cmd_args, char **envp)
{
	char	*with_dot_slash;

	with_dot_slash = ft_strjoin("./", cmd_args[0]);
	execve(with_dot_slash, cmd_args, envp);
	free(with_dot_slash);
	no_such_file(cmd_args[0], cmd_args);
}

void	exec(char *arg, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	if (arg == NULL || arg[0] == '\0')
		command_not_found("\'\'", NULL);
	cmd_args = ft_split(arg, ' ');
	cmd_path = NULL;
	if (ft_strchr(cmd_args[0], '/'))
	{
		if (check_cmd_exist(cmd_args) == OK)
			cmd_path = cmd_args[0];
	}
	else
		cmd_path = get_cmd_path(cmd_args[0], envp);
	if (cmd_path == NULL)
		command_not_found(cmd_args[0], cmd_args);
	if (ft_strcmp(cmd_path, "no path") == 0)
		try_exec_in_pwd(cmd_args, envp);
	execve(cmd_path, cmd_args, envp);
	perror("execve");
	if (cmd_path != cmd_args[0])
		free(cmd_path);
	free_split(cmd_args);
	exit(EXIT_FAILURE);
}
