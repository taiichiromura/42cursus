/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:22:35 by tmura             #+#    #+#             */
/*   Updated: 2025/07/24 14:50:19 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	detect_expand(const char *limiter)
{
	size_t	len;

	if (!limiter)
		return (OK);
	len = ft_strlen(limiter);
	if (len >= 2
		&& ((limiter[0] == '\"' && limiter[len - 1] == '\"')
			|| (limiter[0] == '\'' && limiter[len - 1] == '\'')))
	{
		return (false);
	}
	return (OK);
}

void	do_pipe_bonus(int i, char **argv, int argc, char **envp)
{
	int		fd[2];
	pid_t	process;

	while (i < argc - 2)
	{
		safe_pipe(fd);
		process = fork();
		if (process == CHILD)
		{
			safe_close(fd[0]);
			safe_dup2(fd[1], STDOUT_FILENO);
			safe_close(fd[1]);
			exec(argv[i], envp);
		}
		else
		{
			safe_close(fd[1]);
			safe_dup2(fd[0], STDIN_FILENO);
			safe_close(fd[0]);
		}
		i++;
	}
}

pid_t	last_exec_bonus(char **argv, int argc, char **envp, int start)
{
	int	outfile;
	int	process;

	process = fork();
	if (process == CHILD)
	{
		if (start == HERE_DOC)
			outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (start == INFILE)
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

int	process_input_bonus(char **argv, char **envp, int argc)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < HERE_DOC_SIZE)
			usage_bonus();
		here_document(argv[2], envp);
		return (HERE_DOC);
	}
	else
	{
		open_infile(argv, envp);
		return (INFILE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	last_pid;
	pid_t	pid;
	int		start;
	int		status;
	int		last_status;

	last_status = -1;
	start = 0;
	if (argc < LEAST_ARGS)
		usage_bonus();
	start = process_input_bonus(argv, envp, argc);
	do_pipe_bonus(FIRST_CMD, argv, argc, envp);
	last_pid = last_exec_bonus(argv, argc, envp, start);
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
