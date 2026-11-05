/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_03_execute_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:26:07 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/17 16:12:20 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}

static char	**copy_args(char **args)
{
	int		i;
	int		count;
	char	**copy;

	count = count_args(args);
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(args[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

void	update_underscore_var(t_command *cmd, t_env_var **env_list)
{
	char	*cmd_path;
	char	**args_copy;
	char	*with_dot_slash;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (cmd->builtin != BUILTIN_NONE)
		cmd_path = ft_strdup(cmd->args[0]);
	else
	{
		find_command_path(cmd->args[0], *env_list, &cmd_path);
		if (!cmd_path)
		{
			args_copy = copy_args(cmd->args);
			with_dot_slash = ft_strjoin("./", args_copy[0]);
			cmd_path = with_dot_slash;
			free_array(args_copy);
		}
	}
	if (cmd_path)
	{
		set_env_var(env_list, "_", cmd_path, 1);
		free(cmd_path);
	}
}
