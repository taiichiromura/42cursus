/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   98_free_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:48:18 by ktakeru           #+#    #+#             */
/*   Updated: 2025/08/26 13:09:59 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **envp_array)
{
	int	i;

	if (!envp_array)
		return ;
	i = 0;
	while (envp_array[i] != NULL)
	{
		free(envp_array[i]);
		i++;
	}
	free(envp_array);
}

void	free_env_list(t_env_var *env_list)
{
	t_env_var	*current;
	t_env_var	*next_node;

	current = env_list;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next_node;
	}
}

void	cleanup_exec(char *line, t_token *tokens, t_ast_node *ast)
{
	free_ast(ast);
	free_tokens(tokens);
	free(line);
}
