/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_01_execute_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:46 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/17 20:22:59 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_special_commands(t_command *cmd, t_shell_context *context)
{
	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL
		|| cmd->args[0][0] == '\0')
	{
		context->last_exit_status = 0;
		return (0);
	}
	if (!cmd->next && ft_strcmp(cmd->args[0], "exit") == 0)
	{
		ft_fprintf(STDERR_FILENO, "exit\n");
		return (builtin_exit(cmd->args, context));
	}
	return (-2);
}

int	is_variable_assignment(t_command *cmd)
{
	char	*equal_sign;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (cmd->args[1] != NULL)
		return (0);
	equal_sign = ft_strchr(cmd->args[0], '=');
	if (equal_sign != NULL && equal_sign != cmd->args[0])
	{
		return (1);
	}
	return (0);
}

int	handle_variable_assignment(char *arg, t_env_var **env_list)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	int		status;

	equal_sign = ft_strchr(arg, '=');
	key = ft_strndup(arg, equal_sign - arg);
	if (!key)
		return (1);
	value = equal_sign + 1;
	status = set_env_var(env_list, key, value, 0);
	free(key);
	return (status);
}

static int	execute_command_logic(t_command *cmd, t_env_var **env_list,
		t_shell_context *context)
{
	int	ret;

	if (cmd->next != NULL)
		ret = execute_pipeline(cmd, env_list, context);
	else
		ret = execute_with_redirect(cmd, env_list, context);
	return (ret);
}

int	execute_command(t_command *cmd, t_env_var **env_list,
		t_shell_context *context)
{
	int	ret;

	ret = handle_special_commands(cmd, context);
	if (ret != -2)
	{
		context->last_exit_status = ret;
		return (ret);
	}
	if (is_variable_assignment(cmd) == 1)
	{
		ret = handle_variable_assignment(cmd->args[0], env_list);
		context->last_exit_status = ret;
		return (ret);
	}
	update_underscore_var(cmd, env_list);
	ret = execute_command_logic(cmd, env_list, context);
	if (cmd && ft_strcmp(cmd->args[0], "exit") == 0)
		return (-1);
	context->last_exit_status = ret;
	return (ret);
}
