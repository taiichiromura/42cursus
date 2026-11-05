/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_massages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:47:16 by tmura             #+#    #+#             */
/*   Updated: 2025/07/24 14:12:00 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	command_not_found(char *cmd, char **args)
{
	safe_write(STDERR_FILENO, cmd, ft_strlen(cmd));
	safe_write(STDERR_FILENO, ": command not found\n", 20);
	if (args)
		free_split(args);
	exit(127);
}

void	no_such_file(char *cmd, char **args)
{
	safe_write(STDERR_FILENO, cmd, ft_strlen(cmd));
	safe_write(STDERR_FILENO, ": No such file or directory\n", 28);
	if (args)
		free_split(args);
	exit(127);
}

void	usage(void)
{
	safe_write(STDERR_FILENO, "Bad arguments\n", 14);
	safe_write(STDERR_FILENO,
		"./pipex <file1> <cmd1> <cmd2> <file2>\n", 38);
	exit(EXIT_FAILURE);
}

void	safe_close_and_exit(int fd)
{
	safe_close(fd);
	exit(EXIT_SUCCESS);
}

void	perror_and_exit(char *arg, int fd[2])
{
	safe_close(fd[0]);
	safe_close(fd[1]);
	perror(arg);
	exit(EXIT_FAILURE);
}
