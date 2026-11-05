/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_02_redirect_heredoc4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:03:07 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/02 19:45:22 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_temp_filename(void)
{
	static int	counter = 0;
	char		*count_str;
	char		*filename;

	count_str = ft_itoa(counter++);
	if (!count_str)
		return (NULL);
	filename = ft_strjoin("/tmp/.ms_hd_", count_str);
	free(count_str);
	return (filename);
}

int	prepare_heredoc_file(char **tmp_filename_ptr, int *fd_tmp_ptr)
{
	*tmp_filename_ptr = generate_temp_filename();
	if (!*tmp_filename_ptr)
		return (1);
	*fd_tmp_ptr = open(*tmp_filename_ptr, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*fd_tmp_ptr == -1)
	{
		free(*tmp_filename_ptr);
		return (1);
	}
	return (0);
}

char	*append_value(char *res, char *value)
{
	char	*tmp;

	tmp = ft_strjoin(res, value);
	free(res);
	return (tmp);
}

int	hd_dup2_error(int fd_tmp, char *tmp_filename)
{
	perror("dup2");
	close(fd_tmp);
	unlink(tmp_filename);
	return (1);
}
