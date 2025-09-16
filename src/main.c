/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:10 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/16 17:01:53 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_error(t_p p)
{
	if (p.msg)
		perror(p.msg);
	if (p.infile >= 0)
		close(p.infile);
	if (p.outfile >= 0)
		close(p.outfile);
	if (p.fd[0] >= 0)
		close(p.fd[0]);
	if (p.fd[1] >= 0)
		close(p.fd[1]);
	exit(1);
}

static int	ft_first_child(t_p p)
{
	close(p.fd[0]);
	p.infile = open(p.argv[1], O_RDONLY);
	if (dup2(p.infile, STDIN_FILENO) == -1)
		handle_error(p);
	close(p.infile);
	if (dup2(p.fd[1], STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.fd[1]);
	exec_cmd(p.argv[2], p.envp);
	exit(1);
}

static int	ft_childs(t_p p)
{
	close(p.fd[0]);
	if (dup2(p.pipex, STDIN_FILENO) == -1)
		handle_error(p);
	close(p.pipex);
	if (dup2(p.fd[1], STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.fd[1]);
	exec_cmd(p.argv[2], p.envp);
	exit(1);
}

static int	ft_last_child(t_p p)
{
	if (dup2(p.pipex, STDIN_FILENO) == -1)
		handle_error(p);
	close(p.pipex);
	p.outfile = open(p.argv[p.argc], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (dup2(p.outfile, STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.outfile);
	exec_cmd(p.argv[p.argc - 1], p.envp);
	exit(1);
}

static void	ft_run(t_p p)
{
	p.pid = fork();
	if (p.pid == 0)
		ft_first_child(p);
	p.i = 2;
	while ((++p.i != (p.argc - 1)) && (p.argc != 5))
	{
		if (p.pipex)
			close(p.pipex);
		p.pipex = p.fd[0];
		close(p.fd[1]);
		pipe(p.fd);
		p.pid = fork();
		if (p.pid == 0)
			ft_childs(p);
	}
	close(p.pipex);
	p.pipex = p.fd[0];
	close(p.fd[1]);
	p.pid = fork();
	if (p.pid == 0)
		ft_last_child(p);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_p	p;

	p.argc = argc;
	p.argv = argv;
	p.envp = envp;
	pipe(p.fd);
	ft_run(p);
	while (wait(NULL))
	{
		if (wait(NULL) < 0)
			return (0);
	}
}
