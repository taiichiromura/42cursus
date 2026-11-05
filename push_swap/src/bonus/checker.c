/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:03:37 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 12:34:07 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

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

void	execute_instruction(char *line, t_list_ps **a, t_list_ps **b)
{
	if (!ft_strncmp(line, "sa", 3))
		sa(a);
	else if (!ft_strncmp(line, "sb", 3))
		sb(b);
	else if (!ft_strncmp(line, "ss", 3))
		ss(a, b);
	else if (!ft_strncmp(line, "pa", 3))
		pa(a, b);
	else if (!ft_strncmp(line, "pb", 3))
		pb(a, b);
	else if (!ft_strncmp(line, "ra", 3))
		ra(a);
	else if (!ft_strncmp(line, "rb", 3))
		rb(b);
	else if (!ft_strncmp(line, "rr", 3))
		rr(a, b);
	else if (!ft_strncmp(line, "rra", 4))
		rra(a);
	else if (!ft_strncmp(line, "rrb", 4))
		rrb(b);
	else if (!ft_strncmp(line, "rrr", 4))
		rrr(a, b);
	else
		handle_error(line, a, b);
}

void	read_and_execute(t_list_ps **a, t_list_ps **b)
{
	char	*line;

	while (get_next_line(&line) > 0)
	{
		execute_instruction(line, a, b);
		free(line);
	}
	free(line);
}
