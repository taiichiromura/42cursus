/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:02:07 by tmura             #+#    #+#             */
/*   Updated: 2025/05/22 18:17:51 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	len = 0;
	while (s1[len])
		len++;
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
*/
void	free_and_reset(t_string *str)
{
	if (str->line)
	{
		free(str->line);
		str->line = NULL;
	}
	str->line_length = 0;
	str->saved_size = 0;
}

void	reset_fd_state(t_fd_state *state)
{
	if (state->buffer)
	{
		free(state->buffer);
		state->buffer = NULL;
	}
	state->bytes = 0;
	state->bufp = NULL;
}

char	*handle_error(t_fd_state *state, t_string *str)
{
	free_and_reset(str);
	reset_fd_state(state);
	return (NULL);
}

int	expand_line_buffer(t_string *str)
{
	int		new_size;
	char	*new_line;
	int		i;

	new_size = str->saved_size * 2;
	new_line = malloc(sizeof(char) * new_size);
	if (!new_line)
		return (-1);
	i = 0;
	while (i < str->line_length)
	{
		new_line[i] = str->line[i];
		i++;
	}
	free(str->line);
	str->line = new_line;
	str->saved_size = new_size;
	return (0);
}
