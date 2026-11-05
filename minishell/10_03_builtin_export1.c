/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_03_builtin_export1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:12:10 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/17 16:17:16 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_var	**list_to_array(t_env_var *env_list, int count)
{
	t_env_var	**env_array;
	t_env_var	*current;
	int			i;

	env_array = malloc(sizeof(t_env_var *) * count);
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		env_array[i++] = current;
		current = current->next;
	}
	return (env_array);
}

static void	sort_env_array(t_env_var **env_array, int count)
{
	int			i;
	int			j;
	t_env_var	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env_array[j]->key, env_array[j + 1]->key) > 0)
			{
				temp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_env(t_env_var **env_array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (ft_strcmp(env_array[i]->key, "_") != 0
			&& env_array[i]->is_exported == 1)
		{
			if (env_array[i]->value != NULL)
				ft_printf("declare -x %s=\"%s\"\n", env_array[i]->key,
					env_array[i]->value);
			else
				ft_printf("declare -x %s\n", env_array[i]->key);
		}
		i++;
	}
}

int	print_sorted_env(t_env_var *env_list)
{
	t_env_var	**env_array;
	t_env_var	*current;
	int			count;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	env_array = list_to_array(env_list, count);
	if (!env_array)
		return (1);
	sort_env_array(env_array, count);
	print_env(env_array, count);
	free(env_array);
	return (0);
}

int	builtin_export(char **args, t_env_var **env_list, t_shell_context *context)
{
	int	i;
	int	ret_status;

	i = 1;
	ret_status = 0;
	if (!args[1])
		return (print_sorted_env(*env_list));
	while (args[i])
	{
		if (handle_export_arg(args[i], env_list) != 0)
			ret_status = 1;
		i++;
	}
	context->last_exit_status = ret_status;
	return (ret_status);
}
