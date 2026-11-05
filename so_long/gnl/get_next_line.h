/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:35:03 by tmura             #+#    #+#             */
/*   Updated: 2025/05/22 13:05:46 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_string
{
	char	*line;
	int		line_length;
	int		saved_size;
}			t_string;

typedef struct s_fd_state
{
	int			bytes;
	char		*buffer;
	char		*bufp;
}				t_fd_state;

char	*get_next_line(int fd);
char	*ft_strndup(const char *s1, const int len);
void	free_and_reset(t_string *str);
void	reset_fd_state(t_fd_state *state);
char	*handle_error(t_fd_state *state, t_string *str);
int		expand_line_buffer(t_string *str);
int		ft_getchar(int fd, t_fd_state *state);
int		ft_insert_char_to_line(t_string *str, char c);
char	*finalize_and_return(t_fd_state *state, t_string *str);
int		read_loop(int fd, t_fd_state *state, t_string *str);

#endif
