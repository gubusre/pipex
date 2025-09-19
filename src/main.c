/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gubusque <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/09/10 18:15:10 by gubusque		  #+#	#+#			 */
/*   Updated: 2025/09/19 10:38:37 by gubusque         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

static void	ft_run_l_child(t_p p)
{
	if (p.pid == -1)
	{
		write(2, "zsh: systemcall failed: fork\n", 30);
		close(p.pipex);
		exit(1);
	}
	if (p.pid == 0)
		ft_last_child(p);
}

static void	ft_run_m_child(t_p p)
{
	if (p.pid == -1)
	{
		write(2, "zsh: systemcall failed: fork\n", 30);
		close(p.fd[0]);
		close(p.fd[1]);
		exit(1);
	}
	if (p.pid == 0)
		ft_childs(p);
}

static void	ft_run_f_child(t_p p)
{
	if (p.pid == -1)
	{
		write(2, "zsh: systemcall failed: fork\n", 30);
		close(p.fd[0]);
		close(p.fd[1]);
		exit(1);
	}
	if (p.pid == 0)
		ft_first_child(p);
}

static void	ft_run_father(t_p p)
{
	if (pipe(p.fd) == -1)
	{
		write(2, "zsh: systemcall failed: pipe\n", 30);
		exit(1);
	}
	p.pid = fork();
	ft_run_f_child(p);
	p.pipex = p.fd[0];
	close(p.fd[1]);
	p.i = 3;
	while ((p.argc - 2) > p.i)
	{
		if (pipe(p.fd) == -1)
		{
			write(2, "zsh: systemcall failed: pipe\n", 30);
			exit(1);
		}
		p.pid = fork();
		ft_run_m_child(p);
		p.pipex = p.fd[0];
		close(p.fd[1]);
		p.i++;
	}
	p.pid = fork();
	ft_run_l_child(p);
	close(p.fd[0]);
	close(p.fd[1]);
	close(p.pipex);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_p	p;
	int	status;

	p.argc = argc;
	p.argv = argv;
	p.envp = envp;
	p.e_m = "Invalid number of arguments.";
	p.cmd = "./pipex file1 cmd1 ... cmdN file2";
	p.exit = 0;
	if (p.argc < 5)
		write_e_msg(p);
	else
		ft_run_father(p);
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			p.exit = (WEXITSTATUS(status));
	}
	return (p.exit);
}
