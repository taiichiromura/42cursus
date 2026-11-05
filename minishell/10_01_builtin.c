/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_01_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:11:43 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/18 16:17:30 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_printf("%s\n", cwd);
	return (0);
}

int	builtin_env(t_command *cmd, t_env_var *env_list, t_shell_context *context)
{
	t_env_var	*current;

	if (cmd->args[1])
	{
		ft_fprintf(STDERR_FILENO, "env: '%s': No such file or directory\n",
			cmd->args[1]);
		context->last_exit_status = 127;
		return (127);
	}
	current = env_list;
	while (current)
	{
		if (current->is_exported == 1)
		{
			if (current->key && current->value)
				ft_printf("%s=%s\n", current->key, current->value);
		}
		current = current->next;
	}
	return (0);
}

int	execute_builtin(t_command *cmd, t_env_var **env_list,
		t_shell_context *context)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		context->last_exit_status = 1;
		return (1);
	}
	if (cmd->builtin == BUILTIN_ECHO)
		return (builtin_echo(cmd->args));
	else if (cmd->builtin == BUILTIN_CD)
		return (builtin_cd(cmd->args, env_list, context));
	else if (cmd->builtin == BUILTIN_PWD)
		return (builtin_pwd());
	else if (cmd->builtin == BUILTIN_EXPORT)
		return (builtin_export(cmd->args, env_list, context));
	else if (cmd->builtin == BUILTIN_UNSET)
		return (builtin_unset(cmd->args, env_list));
	else if (cmd->builtin == BUILTIN_ENV)
		return (builtin_env(cmd, *env_list, context));
	else if (cmd->builtin == BUILTIN_EXIT)
		return (builtin_exit(cmd->args, context));
	else
		return (1);
	return (0);
}
