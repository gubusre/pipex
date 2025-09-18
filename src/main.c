/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gubusque <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/09/10 18:15:10 by gubusque		  #+#	#+#			 */
/*   Updated: 2025/09/18 18:50:53 by gubusque         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

static int	ft_first_child(t_p p)
{
	close(p.fd[0]);
	p.cmd = p.argv[1];
	p.infile = open(p.argv[1], O_RDONLY);
	if (p.infile < 0)
		handle_error(p);
	if (dup2(p.infile, STDIN_FILENO) == -1)
		handle_error(p);
	close(p.infile);
	if (dup2(p.fd[1], STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.fd[1]);
	p.cmd = p.argv[2];
	exec_cmd(p);
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
	p.cmd = p.argv[p.i];
	exec_cmd(p);
	exit(1);
}

static int	ft_last_child(t_p p)
{
	if (dup2(p.pipex, STDIN_FILENO) == -1)
		handle_error(p);
	close(p.pipex);
	p.outfile = open(p.argv[p.argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p.outfile < 0)
		handle_error(p);
	if (dup2(p.outfile, STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.outfile);
	p.cmd = p.argv[p.argc - 2];
	exec_cmd(p);
	exit(1);
}

static void	ft_run(t_p p)
{
	int	status;

	if (p.pid == 0)
		ft_first_child(p);
	p.i = 3;
	while ((p.argc - 2) > p.i)
	{
		p.pipex = p.fd[0];
		close(p.fd[1]);
		if (pipe(p.fd) == -1)
		{
			write(2, "zsh: pipe failed\n", 17);
			exit(1);
		}
		p.pid = fork();
		if (p.pid == -1)
		{
			write(2, "zsh: pipe failed\n", 17);
			close(p.fd[0]);
			close(p.fd[1]);
			exit(1);
		}
		if (p.pid == 0)
			ft_childs(p);
		waitpid(p.pid, &status, 0);
		if(WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			close(p.fd[0]);
			close(p.fd[1]);
			exit(WEXITSTATUS(status));
		}
		p.i++;
	}
	p.pipex = p.fd[0];
	close(p.fd[1]);
	p.pid = fork();
	if (p.pid == -1)
	{
		write(2, "zsh: pipe failed\n", 17);
		close(p.fd[0]);
		close(p.fd[1]);
		exit(1);
	}
	if (p.pid == 0 && p.path)
		ft_last_child(p);
}

static void	ft_check(t_p p)
{
	if (p.argc < 5)
	{
		write(2, "Not enoguht arguments\n", 22);
		exit(1);
	}
	pipe(p.fd);
	if (pipe(p.fd) == -1)
	{
		write(2, "zsh: pipe failed\n", 17);
		exit(1);
	}
	p.pid = fork();
	if (p.pid == -1)
	{
		write(2, "zsh: fork failed\n", 17);
		close(p.fd[0]);
		close(p.fd[1]);
		exit(1);
	}
	ft_run(p);
	close(p.fd[0]);
	close(p.fd[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_p	p;
	int	status;

	p.argc = argc;
	p.argv = argv;
	p.envp = envp;
	p.norminette = 0;
	ft_check(p);
	while (wait(&status) >= 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (WEXITSTATUS(status));
	}
	return (0);
}
