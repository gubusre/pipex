/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:10 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/15 15:47:30 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void    child(int dup_stdin, int dup_stdout, int to_close,
		char *cmd, char **envp)
{
	close(to_close);
	dup2(dup_stdin, STDIN_FILENO);
	close(dup_stdin);
	dup2(dup_stdout, STDOUT_FILENO);
	close(dup_stdout);
	exec_cmd(cmd, envp);
}

int	main(int argc, char  *argv[], char *envp[])
{
	pid_t	pid1;
	pid_t	pid2;
	int	fd_in;
	int	fd_out;
	int	pipe_fd[2];

	if (argc != 5)
	{
		write (2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
		exit(1);
	}
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
	{
		perror(argv[1]);
		exit(1);
	}
	fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror(argv[4]);
		close(fd_in);
		exit(1);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		close(fd_in);
		close(fd_out);
		exit(1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid1 == 0)
		child (fd_in, pipe_fd[1], pipe_fd[0], argv[2], envp);
	close(fd_in);
	close(pipe_fd[1]);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid2 == 0)
		child (pipe_fd[0], fd_out, pipe_fd[1], argv[3], envp);
	close(fd_out);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
