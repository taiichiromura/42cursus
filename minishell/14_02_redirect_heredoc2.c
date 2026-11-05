/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_02_redirect_heredoc2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:11:28 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/17 14:55:29 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_heredoc(char *line, t_heredoc_data *data)
{
	char	*expanded_line;

	expanded_line = expand_env_heredoc(line, data->envp, data->context);
	if (!expanded_line)
	{
		free(line);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(expanded_line, data->fd_tmp);
	free(expanded_line);
	return (0);
}

static int	process_heredoc_input(t_heredoc_data *data)
{
	char	*line;

	line = readline("> ");
	if (line == NULL)
		return (1);
	if (ft_strcmp(line, data->delimiter) == 0)
	{
		free(line);
		return (2);
	}
	if (data->expand)
	{
		if (expand_heredoc(line, data) != 0)
		{
			free(line);
			return (3);
		}
	}
	else
		ft_putendl_fd(line, data->fd_tmp);
	free(line);
	return (0);
}

static int	heredoc_input_loop(t_heredoc_data *data)
{
	char	*trimmed_delimiter;
	int		status;

	trimmed_delimiter = remove_quotes(data->delimiter);
	if (!trimmed_delimiter)
		return (EXIT_FAILURE);
	data->delimiter = trimmed_delimiter;
	data->expand = !is_quoted(data->delimiter);
	while (1)
	{
		status = process_heredoc_input(data);
		if (status == 1)
			return (free(trimmed_delimiter), 130);
		if (status == 2)
			break ;
		if (status == 3)
			return (free(trimmed_delimiter), EXIT_FAILURE);
	}
	free(trimmed_delimiter);
	return (EXIT_SUCCESS);
}

void	execute_child_heredoc(const char *delimiter, int fd_tmp, char **envp,
		t_shell_context *context)
{
	int				exit_code;
	int				i;
	t_heredoc_data	data;

	i = 3;
	while (i < MAX_FD_SCAN)
	{
		if (i == fd_tmp)
		{
			i++;
			continue ;
		}
		close(i);
		i++;
	}
	data.delimiter = delimiter;
	data.fd_tmp = fd_tmp;
	data.envp = envp;
	data.context = context;
	exit_code = heredoc_input_loop(&data);
	close(fd_tmp);
	exit(exit_code);
}

int	wait_for_child_heredoc(pid_t pid, int *status)
{
	int	result;

	while (1)
	{
		result = waitpid(pid, status, 0);
		if (result == -1 && errno == EINTR)
			continue ;
		break ;
	}
	return (result);
}
