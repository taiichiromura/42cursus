/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:03:58 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/19 15:54:14 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

t_env_var	*setup_env_and_signal(char **envp)
{
	t_env_var	*env_list;

	env_list = create_env_list(envp);
	if (!env_list)
		return (NULL);
	setup_parent_signals();
	return (env_list);
}

int	is_blank_line(char *line)
{
	if (!line)
		return (1);
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

static int	handle_execution(char *line, t_ast_node *ast, t_env_var **env_list,
		t_shell_context *context)
{
	int	exit_status;

	if (expand_ast(ast, *env_list, context) != 0)
	{
		free(line);
		free_ast(ast);
		return (context->last_exit_status);
	}
	exit_status = execute_ast(ast, env_list, context);
	free(line);
	free_ast(ast);
	return (exit_status);
}

int	execute_command_line(char *line, t_env_var **env_list,
		t_shell_context *context)
{
	t_token		*tokens;
	t_ast_node	*ast;
	int			val_stat;

	if (is_blank_line(line))
		return (free(line), 0);
	tokens = lexer(line);
	if (!tokens)
		return (free(line), 1);
	val_stat = validate_syntax(tokens);
	if (val_stat != 0)
	{
		free_tokens(tokens);
		context->last_exit_status = 258;
		return (free(line), 258);
	}
	ast = parse_tokens(tokens);
	free_tokens(tokens);
	if (!ast)
	{
		context->last_exit_status = 1;
		return (free(line), 1);
	}
	context->last_exit_status = handle_execution(line, ast, env_list, context);
	return (context->last_exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_env_var		*env_list;
	char			*command_line;
	t_shell_context	context;

	context.last_exit_status = 0;
	env_list = setup_env_and_signal(envp);
	if (!env_list)
		return (1);
	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
	{
		command_line = ft_strdup(argv[2]);
		if (!command_line)
		{
			free_env_list(env_list);
			return (1);
		}
		context.last_exit_status = execute_command_line(command_line, &env_list,
				&context);
	}
	else
		minishell_loop(&env_list, &context);
	free_env_list(env_list);
	return (context.last_exit_status);
}
