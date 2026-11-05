/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_create_env_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:48:09 by ktakeru           #+#    #+#             */
/*   Updated: 2025/08/19 18:08:43 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	assign_node_members(t_env_var *node, char *envp_str, char *eq_sign)
{
	node->key = ft_strndup(envp_str, eq_sign - envp_str);
	if (!node->key)
		return (1);
	node->value = ft_strdup(eq_sign + 1);
	if (!node->value)
	{
		free(node->key);
		return (1);
	}
	return (0);
}

t_env_var	*create_env_node(char *envp_str)
{
	t_env_var	*new_node;
	char		*eq_sign;

	eq_sign = ft_strchr(envp_str, '=');
	if (!eq_sign)
		return (NULL);
	new_node = malloc(sizeof(t_env_var));
	if (!new_node)
		return (NULL);
	if (assign_node_members(new_node, envp_str, eq_sign))
	{
		free(new_node);
		return (NULL);
	}
	new_node->is_exported = 1;
	new_node->next = NULL;
	return (new_node);
}

static void	add_env_node_to_list(t_env_var **head, t_env_var **current,
		t_env_var *new_node)
{
	if (*head == NULL)
	{
		*head = new_node;
		*current = *head;
	}
	else
	{
		(*current)->next = new_node;
		*current = new_node;
	}
}

t_env_var	*create_env_list(char **envp)
{
	t_env_var	*head;
	t_env_var	*current;
	int			i;
	t_env_var	*new_node;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		new_node = create_env_node(envp[i]);
		if (new_node != NULL)
		{
			add_env_node_to_list(&head, &current, new_node);
		}
		i++;
	}
	return (head);
}
