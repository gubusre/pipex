/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:10 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/17 18:21:45 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_first_child(t_p p)
{
	close(p.fd[0]);
	close(p.pipex);
	p.infile = open(p.argv[1], O_RDONLY);
	if (p.infile < 0)
		handle_error(p);
	if (dup2(p.infile, STDIN_FILENO) == -1)
		handle_error(p);
	close(p.infile);
	if (dup2(p.fd[1], STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.fd[1]);
	if (p.argc == 3)
		exec_cmd(p.cmd, p.envp);
	if (p.argc > 3)
		exec_cmd(p.argv[2], p.envp);
	exit(1);
}

static int	ft_childs(t_p p)
{
	if (dup2(p.pipex, STDIN_FILENO) == -1)
		handle_error(p);
	close(p.pipex);
	if (dup2(p.fd[1], STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.fd[1]);
	if (p.argc > 4)
		exec_cmd(p.argv[p.i], p.envp);
	exit(1);
}

static int	ft_last_child(t_p p)
{
	if (dup2(p.pipex, STDIN_FILENO) == -1)
		handle_error(p);
	close(p.pipex);
	p.outfile = open(p.argv[p.argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (dup2(p.outfile, STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.outfile);
	if (p.argc == 3)
		exec_cmd(p.cmd, p.envp);
	if (p.argc > 3)
		exec_cmd(p.argv[p.argc - 2], p.envp);
	exit(1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_p	p;

	p.argc = argc;
	p.argv = argv;
	p.envp = envp;
	if (p.argc < 3)
		handle_error(p);
	if (p.argc == 3)
		p.cmd = "cat ";
	pipe(p.fd);
	p.pid = fork();
	if (p.pid == 0)
		ft_first_child(p);
	p.i = 1;
	if (p.argc > 4)
	{
		while ((p.argc - 2) > ++p.i && (p.i < (p.argc - 2)))
		{
			p.pipex = p.fd[0];
			close(p.fd[1]);
			pipe(p.fd);
			p.pid = fork();
			if (p.pid == 0)
				ft_childs(p);
		}
	}
	p.pipex = p.fd[0];
	close(p.fd[1]);
	p.pid = fork();
	if (p.pid == 0)
		ft_last_child(p);
	while (wait(NULL))
	{
		if (wait(NULL) < 0)
			return (0);
	}
}
