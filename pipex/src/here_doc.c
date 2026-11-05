/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:47:57 by tmura             #+#    #+#             */
/*   Updated: 2025/07/08 17:33:56 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*expand_buffer(char *buffer, int *capacity, int length)
{
	int		new_capacity;
	char	*new_buffer;
	int		i;

	new_capacity = *capacity * 2;
	new_buffer = malloc(new_capacity);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (i < length)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	*capacity = new_capacity;
	return (new_buffer);
}

int	read_line(char *buffer, int capacity)
{
	int		size;
	char	c;
	int		i;

	i = 0;
	size = read(STDIN_FILENO, &c, 1);
	while (size > 0)
	{
		if (c == '\n')
			break ;
		if (i + 2 >= capacity)
		{
			buffer = expand_buffer(buffer, &capacity, i);
			if (!buffer)
				return (ERROR);
		}
		buffer[i++] = c;
		size = read(STDIN_FILENO, &c, 1);
	}
	buffer[i] = '\0';
	if (size < 0)
		return (ERROR);
	if (size == 0 && i == 0)
		return (0);
	return (1);
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		capacity;
	int		read_size;

	capacity = INIT_CAPACITY;
	buffer = malloc(capacity);
	if (!buffer)
		return (ERROR);
	read_size = read_line(buffer, capacity);
	if (read_size == ERROR)
	{
		free(buffer);
		return (ERROR);
	}
	*line = buffer;
	return (read_size);
}

void	put_line(char *limiter, int fd[2], char **envp, int expand)
{
	char	*line;
	char	*expanded;

	safe_write(STDOUT_FILENO, "> ", 2);
	if (get_next_line(&line) == 0)
	{
		safe_write(STDOUT_FILENO, "\n", 1);
		free(line);
		safe_close_and_exit(fd[1]);
	}
	if (ft_strcmp(limiter, line) == 0)
	{
		free(line);
		safe_close_and_exit(fd[1]);
	}
	if (expand)
	{
		expanded = expand_env(line, envp);
		safe_write(fd[1], expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		safe_write(fd[1], line, ft_strlen(line));
	safe_write(fd[1], "\n", 1);
	free(line);
}

void	here_document(char *limiter, char **envp)
{
	int	fd[2];
	int	process;
	int	expand;

	safe_pipe(fd);
	process = fork();
	if (process == ERROR)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (process == CHILD)
	{
		expand = detect_expand(limiter);
		safe_close(fd[0]);
		while (1)
			put_line(limiter, fd, envp, expand);
	}
	else
	{
		safe_close(fd[1]);
		safe_dup2(fd[0], STDIN_FILENO);
		safe_close(fd[0]);
		wait(NULL);
	}
}
