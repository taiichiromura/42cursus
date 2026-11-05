/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:57:33 by tmura             #+#    #+#             */
/*   Updated: 2025/07/24 18:51:53 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

# define ERROR -1
# define OK 1
# define CHILD 0
# define LEAST_ARGS 5

int		get_next_line(char **line);
void	free_split(char **contents);
int		check_cmd_exist(char **argv);
char	*get_cmd_path(char *arg_cmd, char **envp);
char	*resolve_command(char *arg_cmd, char *cmd_env);
void	exec(char *arg, char **envp);
void	do_pipe(char **argv, char **envp);
pid_t	last_exec(char **argv, int argc, char **envp);
int		process_input(char **argv);
void	safe_write(int fd, const void *buf, size_t n);
void	safe_dup2(int fd, int std_filenum);
void	safe_pipe(int fd[2]);
void	safe_close(int fd);
void	open_infile(char **argv, char **envp);
void	command_not_found(char *cmd, char **args);
void	usage(void);
void	no_such_file(char *cmd, char **args);
int		ft_strcmp(const char *s1, const char *s2);
void	perror_and_exit(char *arg, int fd[2]);

#endif
