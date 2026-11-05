/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:01:56 by tmura             #+#    #+#             */
/*   Updated: 2025/05/21 14:39:05 by tmura            ###   ########.fr       */
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
		state->cursor = state->buffer;
	}
	state->bytes--;
	return (*state->cursor++);
}

int	ft_insert_char_to_line(t_string *str, char character)
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
	str->line[str->line_length++] = character;
	return (0);
}

char	*finalize_and_return(t_fd_state *state, t_string *str)
{
	char	*return_line;
	int		i;

	if (ft_insert_char_to_line(str, '\0') == -1)
		return (handle_error(state, str));
	return_line = malloc(str->line_length);
	if (!return_line)
		return (handle_error(state, str));
	i = 0;
	while (i < str->line_length)
	{
		return_line[i] = str->line[i];
		i++;
	}
	free_and_reset(str);
	return (return_line);
}

int	read_loop(int fd, t_fd_state *state, t_string *str)
{
	int	character;

	while (1)
	{
		character = ft_getchar(fd, state);
		if (character == -42)
			return (-1);
		if (character == EOF)
			return (0);
		if (ft_insert_char_to_line(str, character) == -1)
			return (-1);
		if (character == '\n')
			break ;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_fd_state	fds;
	t_fd_state			*state;
	t_string			str;
	int					read_result;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	state = &fds;
	str.line = NULL;
	str.line_length = 0;
	str.saved_size = 0;
	read_result = read_loop(fd, state, &str);
	if (read_result == -1)
		return (handle_error(state, &str));
	if (str.line_length > 0 || str.line != NULL)
		return (finalize_and_return(state, &str));
	return (handle_error(state, &str));
}
