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
		p.cmd = "fork";
		close(p.pipex);
		write_e_msg(p);
	}
	if (p.pid == 0)
		ft_last_child(p);
}

static void	ft_run_m_child(t_p p)
{
	if (p.pid == -1)
	{
		p.cmd = "fork";
		close(p.fd[0]);
		close(p.fd[1]);
		write_e_msg(p);
	}
	if (p.pid == 0)
		ft_childs(p);
}

static void	ft_run_f_child(t_p p)
{
	if (p.pid == -1)
	{
		p.cmd = "fork";
		close(p.fd[0]);
		close(p.fd[1]);
		write_e_msg(p);
	}
	if (p.pid == 0)
		ft_first_child(p);
}

static void	ft_run_father(t_p p)
{
	p.path_str = ft_find_path(p);
	if (pipe(p.fd) == -1)
		write_e_msg(p);
	p.pid = fork();
	ft_run_f_child(p);
	p.pipex = p.fd[0];
	close(p.fd[1]);
	p.i = 3;
	while ((p.argc - 2) > p.i)
	{
		if (pipe(p.fd) == -1)
			write_e_msg(p);
		p.pid = fork();
		ft_run_m_child(p);
		p.pipex = p.fd[0];
		close(p.fd[1]);
		p.i++;
	}
	p.pid = fork();
	ft_run_l_child(p);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_p	p;

	p.argc = argc;
	p.argv = argv;
	p.envp = envp;
	p.cmd = p.argv[0];
	p.e_m = "systemcall failed";
	p.cmd = "pipe";
	if (p.argc < 5)
	{
		p.e_m = "Invalid number of arguments.";
		p.cmd = "./pipex file1 cmd1 ... cmdN file2";
		write_e_msg(p);
	}
	else
		ft_run_father(p);
	close(p.fd[0]);
	close(p.fd[1]);
	close(p.pipex);
	while (wait(NULL) > 0)
		;
	return (0);
}
