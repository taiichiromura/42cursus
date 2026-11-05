/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_error_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:09:35 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/15 20:26:08 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_tmp_open_error(char *tmp_filename)
{
	fd_error(tmp_filename);
	free(tmp_filename);
	return (1);
}

int	fd_tmp_fork_error(int fd_tmp, char *tmp_filename)
{
	perror("fork");
	close(fd_tmp);
	free(tmp_filename);
	return (1);
}

int	open_error(void)
{
	ft_fprintf(STDERR_FILENO, "minishell: open: %s\n", strerror(errno));
	return (1);
}
