/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:10 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/17 12:44:49 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_first_child(t_p p)
{
	printf("FIRST CHILD\n");
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
	printf("MID CHILD\n");
	close(p.fd[0]);
	if (dup2(p.pipex, STDIN_FILENO) == -1)
		handle_error(p);
	close(p.pipex);
	if (dup2(p.fd[1], STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.fd[1]);
	printf("first child");
	exec_cmd(p.argv[p.i], p.envp);
	exit(1);
}

static int	ft_last_child(t_p p)
{
	printf("LAST CHILD\n");
	if (dup2(p.pipex, STDIN_FILENO) == -1)
		handle_error(p);
	close(p.pipex);
	p.outfile = open(p.argv[p.argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (dup2(p.outfile, STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.outfile);
	exec_cmd(p.argv[p.argc - 2], p.envp);
	exit(1);
}

static void	ft_run(t_p p)
{
	if (p.pipex > 0)
		close(p.pipex);
	p.pipex = p.fd[0];
	close(p.fd[1]);
	pipe(p.fd);
	p.pid = fork();
	if (p.pid == 0)
		ft_childs(p);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_p	p;

	p.argc = argc;
	p.argv = argv;
	p.envp = envp;
	pipe(p.fd);
	p.pid = fork();
	if (p.pid == 0)
		ft_first_child(p);
	ft_run(p);
	close(p.pipex);
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
