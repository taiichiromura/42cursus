/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_01_redirect2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:27:45 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/02 21:28:00 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_red_in(t_redirect *current_list)
{
	int	fd;

	fd = open(current_list->filename, O_RDONLY);
	if (fd == -1)
		return (fd_error(current_list->filename), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (dup2_error(), 1);
	close(fd);
	return (0);
}

int	handle_red_out(t_redirect *current_list)
{
	int	fd;

	fd = open(current_list->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (fd_error(current_list->filename), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (dup2_error(), 1);
	close(fd);
	return (0);
}

int	handle_red_append(t_redirect *current_list)
{
	int	fd;

	fd = open(current_list->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (fd_error(current_list->filename), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (dup2_error(), 1);
	close(fd);
	return (0);
}
