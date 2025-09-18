/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gubusque <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/09/10 18:15:10 by gubusque		  #+#	#+#			 */
/*   Updated: 2025/09/18 20:48:45 by gubusque         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

static void	ft_run(t_p p)
{
	int	status;

	if (p.pid == 0)
		ft_first_child(p);
	else
	{
		p.pipex = p.fd[0];
		close(p.fd[1]);
	}
	p.i = 3;
	while ((p.argc - 2) > p.i)
	{
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
		close(p.pipex);
		close(p.fd[1]);
		waitpid(p.pid, &status, 0);
		if (WIFEXITED(status))
			p.norminette = (WEXITSTATUS(status));
		p.pipex = p.fd[0];
		p.i++;
	}
	p.pid = fork();
	if (p.pid == -1)
	{
		write(2, "zsh: pipe failed\n", 17);
		close(p.pipex);
		exit(1);
	}
	if (p.pid == 0)
		ft_last_child(p);
	close(p.pipex);
}

static void	ft_check(t_p p)
{
	if (p.argc < 5)
	{
		write(2, "Not enoguht arguments\n", 22);
		exit(1);
	}
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
	close(p.fd[0]);
	close(p.fd[1]);
	while (wait(&status) >= 0)
	{
		if (WIFEXITED(status))
			p.norminette = (WEXITSTATUS(status));
	}
	return (p.norminette);
}
