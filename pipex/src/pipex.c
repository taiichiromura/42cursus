/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:20:42 by tmura             #+#    #+#             */
/*   Updated: 2025/07/24 14:50:15 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

pid_t	last_exec(char **argv, int argc, char **envp)
{
	int		outfile;
	int		process;

	process = fork();
	if (process == CHILD)
	{
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == ERROR)
		{
			perror(argv[argc - 1]);
			exit(EXIT_FAILURE);
		}
		safe_dup2(outfile, STDOUT_FILENO);
		safe_close(outfile);
		exec(argv[argc - 2], envp);
		exit(EXIT_FAILURE);
	}
	return (process);
}

void	do_pipe(char **argv, char **envp)
{
	int		fd[2];
	pid_t	process;

	safe_pipe(fd);
	process = fork();
	if (process == CHILD)
	{
		safe_close(fd[0]);
		safe_dup2(fd[1], STDOUT_FILENO);
		safe_close(fd[1]);
		exec(argv[2], envp);
	}
	else
	{
		safe_close(fd[1]);
		safe_dup2(fd[0], STDIN_FILENO);
		safe_close(fd[0]);
	}
}

void	open_infile(char **argv, char **envp)
{
	pid_t	infile;
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

int	main(int argc, char **argv, char **envp)
{
	pid_t	last_pid;
	pid_t	pid;
	int		status;
	int		last_status;

	last_status = -1;
	if (argc != LEAST_ARGS)
		usage();
	open_infile(argv, envp);
	last_pid = last_exec(argv, argc, envp);
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == last_pid)
			last_status = status;
		pid = waitpid(-1, &status, 0);
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else
		return (1);
}
