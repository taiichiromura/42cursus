/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_02_builtin_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:02:15 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/15 20:19:51 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getenv_val(t_env_var *env_list, const char *key)
{
	while (env_list != NULL)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

static int	change_dir_and_update_env(char *path, t_env_var **env_list,
		char *old_pwd, t_shell_context *context)
{
	char	new_pwd[1024];

	if (chdir(path) != 0)
	{
		ft_fprintf(STDERR_FILENO, "bash: cd: %s: No such file or directory\n",
			path);
		context->last_exit_status = 1;
		return (1);
	}
	if (!getcwd(new_pwd, sizeof(new_pwd)))
	{
		perror("bash: cd: getcwd failed");
		context->last_exit_status = 1;
		return (1);
	}
	if (set_env_var(env_list, "OLDPWD", old_pwd, 1) != 0
		|| set_env_var(env_list, "PWD", new_pwd, 1) != 0)
	{
		context->last_exit_status = 1;
		return (1);
	}
	context->last_exit_status = 0;
	return (0);
}

static char	*get_cd_target_path(char **args, t_env_var **env_list,
		t_shell_context *context)
{
	char	*home;
	char	*oldpwd;

	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		home = my_getenv_val(*env_list, "HOME");
		if (!home)
		{
			return (context->last_exit_status = 1, NULL);
		}
		return (home);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		oldpwd = my_getenv_val(*env_list, "OLDPWD");
		if (!oldpwd)
		{
			ft_fprintf(STDERR_FILENO, "bash: cd: OLDPWD not set\n");
			context->last_exit_status = 1;
			return (NULL);
		}
		ft_printf("%s\n", oldpwd);
		return (oldpwd);
	}
	return (args[1]);
}

int	builtin_cd(char **args, t_env_var **env_list, t_shell_context *context)
{
	char	*old_pwd;
	char	*path;
	int		ret;

	if (args[2] != NULL)
	{
		context->last_exit_status = 1;
		ft_fprintf(STDERR_FILENO, "bash: cd: too many arguments\n");
		return (1);
	}
	old_pwd = my_getenv_val(*env_list, "PWD");
	path = get_cd_target_path(args, env_list, context);
	if (path == NULL)
		return (context->last_exit_status);
	ret = change_dir_and_update_env(path, env_list, old_pwd, context);
	return (ret);
}
