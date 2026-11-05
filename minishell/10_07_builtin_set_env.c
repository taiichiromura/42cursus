/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_06_builtin_set_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 22:11:39 by ktakeru           #+#    #+#             */
/*   Updated: 2025/08/19 18:07:36 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_var	*find_env_var(t_env_var *env_list, const char *key)
{
	t_env_var	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static int	update_existing_env_var(t_env_var *node, const char *value)
{
	if (node->value)
		free(node->value);
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (1);
	}
	else
		node->value = NULL;
	return (0);
}

static t_env_var	*create_env_var_node(const char *key, const char *value,
		int is_exported)
{
	t_env_var	*new_node;

	new_node = malloc(sizeof(t_env_var));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return (free(new_node), NULL);
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
		{
			free(new_node->key);
			free(new_node);
			return (NULL);
		}
	}
	else
		new_node->value = NULL;
	new_node->is_exported = is_exported;
	new_node->next = NULL;
	return (new_node);
}

static int	add_new_env_var(t_env_var **env_list, const char *key,
		const char *value, int is_exported)
{
	t_env_var	*new_node;
	t_env_var	*current;

	new_node = create_env_var_node(key, value, is_exported);
	if (!new_node)
		return (1);
	if (*env_list == NULL)
		*env_list = new_node;
	else
	{
		current = *env_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (0);
}

int	set_env_var(t_env_var **env_list, const char *key, const char *value,
		int is_exported)
{
	t_env_var	*node_to_update;
	int			status;

	if (!key)
		return (1);
	node_to_update = find_env_var(*env_list, key);
	if (node_to_update)
	{
		status = update_existing_env_var(node_to_update, value);
		if (is_exported == 1)
			node_to_update->is_exported = 1;
		return (status);
	}
	else
	{
		return (add_new_env_var(env_list, key, value, is_exported));
	}
}
