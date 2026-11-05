/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:32:52 by tmura             #+#    #+#             */
/*   Updated: 2025/09/19 16:08:18 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (s1);
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

static int	handle_incomplete_line(char **line)
{
	char	*cont;
	t_token	*temp_tokens;
	int		syntax_status;

	while (1)
	{
		cont = readline("> ");
		if (!cont)
			return (free(*line), 0);
		if (*cont == '\0')
		{
			free(cont);
			free(*line);
			return (0);
		}
		*line = ft_strjoin_free(*line, "\n");
		*line = ft_strjoin_free(*line, cont);
		free(cont);
		temp_tokens = lexer(*line);
		syntax_status = validate_syntax(temp_tokens);
		free_tokens(temp_tokens);
		if (syntax_status != 2)
			break ;
	}
	return (1);
}

static int	process_command_tokens(char **line, t_shell_context *context)
{
	t_token	*tokens;
	int		syntax_status;

	tokens = lexer(*line);
	if (!tokens)
	{
		free(*line);
		*line = NULL;
		context->last_exit_status = 1;
		return (-1);
	}
	syntax_status = validate_syntax(tokens);
	free_tokens(tokens);
	if (syntax_status == 2 && !handle_incomplete_line(line))
		return (-1);
	return (syntax_status);
}

static char	*read_and_handle_line(t_shell_context *context)
{
	char	*line;

	line = readline("minishell$ ");
	if (g_sigint_received)
	{
		context->last_exit_status = 130;
		g_sigint_received = 0;
	}
	if (!line)
	{
		ft_printf("exit\n");
		context->last_exit_status = 0;
		return (NULL);
	}
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
}

int	minishell_loop(t_env_var **env_list, t_shell_context *context)
{
	char	*line;
	int		syntax_status;

	while (1)
	{
		line = read_and_handle_line(context);
		if (!line)
			return (context->last_exit_status);
		if (is_blank_line(line))
		{
			free(line);
			continue ;
		}
		syntax_status = process_command_tokens(&line, context);
		if (syntax_status == -1)
			return (context->last_exit_status);
		if (syntax_status != 2)
			execute_command_line(line, env_list, context);
	}
}
