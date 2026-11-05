/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:49:47 by tmura             #+#    #+#             */
/*   Updated: 2025/07/24 14:53:15 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	open_infile(char **argv, char **envp)
{
	int		infile;
	int		fd[2];
	pid_t	pid;

	safe_pipe(fd);
	pid = fork();
	if (pid == CHILD)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile == ERROR)
			perror_and_exit(argv[1], fd);
		safe_close(fd[0]);
		safe_dup2(infile, STDIN_FILENO);
		safe_dup2(fd[1], STDOUT_FILENO);
		safe_close(infile);
		safe_close(fd[1]);
		exec(argv[2], envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		safe_close(fd[1]);
		safe_dup2(fd[0], STDIN_FILENO);
		safe_close(fd[0]);
	}
}

void	free_split(char **contents)
{
	int	i;

	i = 0;
	while (contents[i])
	{
		free(contents[i]);
		i++;
	}
	free(contents);
}
