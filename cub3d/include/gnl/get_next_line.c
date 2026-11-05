/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:01:56 by tmura             #+#    #+#             */
/*   Updated: 2026/05/13 10:14:05 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_getchar(int fd, t_fd_state *state)
{
	int	read_bytes;

	if (!state->buffer)
	{
		state->buffer = malloc(BUFFER_SIZE);
		if (!state->buffer)
			return (-42);
	}
	if (state->bytes == 0)
	{
		read_bytes = read(fd, state->buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (-42);
		if (read_bytes == 0)
			return (EOF);
		state->bytes = read_bytes;
		state->bufp = state->buffer;
	}
	state->bytes--;
	return (*state->bufp++);
}

int	ft_insert_char_to_line(t_string *str, char c)
{
	if (!str->line)
	{
		str->saved_size = 16;
		str->line = malloc(sizeof(char) * str->saved_size);
		if (!str->line)
			return (-1);
	}
	if (str->line_length + 2 >= str->saved_size)
		if (expand_line_buffer(str) == -1)
			return (-1);
	str->line[str->line_length++] = c;
	return (0);
}

char	*finalize_and_return(t_fd_state *state, t_string *str)
{
	char	*ret;
	int		i;

	if (ft_insert_char_to_line(str, '\0') == -1)
		return (handle_error(state, str));
	ret = malloc(str->line_length);
	if (!ret)
		return (handle_error(state, str));
	i = 0;
	while (i < str->line_length)
	{
		ret[i] = str->line[i];
		i++;
	}
	free_and_reset(str);
	return (ret);
}

int	read_loop(int fd, t_fd_state *state, t_string *str)
{
	int	c;

	while (1)
	{
		c = ft_getchar(fd, state);
		if (c == -42)
			return (-1);
		if (c == EOF)
			return (0);
		if (ft_insert_char_to_line(str, c) == -1)
			return (-1);
		if (c == '\n')
			break ;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_fd_state	fds;
	t_fd_state			*state;
	t_string			str;
	int					res;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	state = &fds;
	str.line = NULL;
	str.line_length = 0;
	str.saved_size = 0;
	res = read_loop(fd, state, &str);
	if (res == -1)
		return (handle_error(state, &str));
	if (str.line_length > 0 || str.line != NULL)
		return (finalize_and_return(state, &str));
	return (handle_error(state, &str));
}
/*
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"
int main(void)
{
	const char *filename = "giant_line.txt";
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open file");
		return 1;
	}

	char *line = get_next_line(fd);
	if (!line)
	{
		printf("get_next_line returned NULL\n");
	}
	else
	{
		printf("Line read successfully! Length: %zu\n", strlen(line));
		free(line);
	}
	close(fd);
	return 0;
}
*/
