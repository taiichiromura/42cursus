/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_03_env_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:07:04 by ktakeru           #+#    #+#             */
/*   Updated: 2025/08/19 18:12:07 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_nodes(t_env_var *env_list)
{
	int	count;

	count = 0;
	while (env_list != NULL)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

static void	free_partial_array(char **array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	create_and_assign_string(char **array, t_env_var *node, int index)
{
	size_t	len;

	len = ft_strlen(node->key) + ft_strlen(node->value) + 2;
	array[index] = (char *)malloc(len);
	if (array[index] == NULL)
		return (1);
	ft_strcpy(array[index], node->key);
	ft_strcat(array[index], "=");
	ft_strcat(array[index], node->value);
	return (0);
}

static int	assign_envp_array(char **envp_array, t_env_var *env_list)
{
	int	i;

	i = 0;
	while (env_list != NULL)
	{
		if (create_and_assign_string(envp_array, env_list, i) != 0)
		{
			free_partial_array(envp_array, i);
			return (1);
		}
		env_list = env_list->next;
		i++;
	}
	envp_array[i] = NULL;
	return (0);
}

char	**generate_envp_for_execve(t_env_var *env_list)
{
	char	**envp_array;
	int		count;

	count = count_env_nodes(env_list);
	envp_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (envp_array == NULL)
		return (NULL);
	if (assign_envp_array(envp_array, env_list))
	{
		return (NULL);
	}
	return (envp_array);
}
