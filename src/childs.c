/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:22:31 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/18 20:18:38 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_last_child(t_p p)
{
	p.cmd = p.argv[p.argc - 2];
	if (!p.cmd || !p.cmd[0])
		handle_error(p);
	if (dup2(p.pipex, STDIN_FILENO) == -1)
		handle_error(p);
	close(p.pipex);
	p.outfile = open(p.argv[p.argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p.outfile < 0)
		handle_error(p);
	if (dup2(p.outfile, STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.outfile);
	exec_cmd(p);
	exit(1);
}

int	ft_childs(t_p p)
{
	p.cmd = p.argv[p.i];
	if (!p.cmd || !p.cmd[0])
		handle_error(p);
	if (dup2(p.pipex, STDIN_FILENO) == -1)
		handle_error(p);
	close(p.pipex);
	if (dup2(p.fd[1], STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.fd[1]);
	close(p.fd[0]);
	exec_cmd(p);
	exit(1);
}

int	ft_first_child(t_p p)
{
	close(p.fd[0]);
	close(p.pipex);
	p.cmd = p.argv[1];
	p.infile = open(p.argv[1], O_RDONLY);
	if (p.infile < 0)
		handle_error(p);
	if (dup2(p.infile, STDIN_FILENO) == -1)
		handle_error(p);
	p.cmd = p.argv[2];
	if (!p.cmd || !p.cmd[0])
		handle_error(p);
	close(p.infile);
	if (dup2(p.fd[1], STDOUT_FILENO) == -1)
		handle_error(p);
	close(p.fd[1]);
	exec_cmd(p);
	exit(1);
}

void	write_e_msg(t_p p)
{
	char	*msg;
	char	*temp;

	msg = ft_strjoin("zsh: ", p.e_m);
	if (!msg)
		exit(1);
	temp = msg;
	if (p.argc < 5)
		msg = ft_strjoin(temp, "\nUsage: ");
	else
		msg = ft_strjoin(temp, ": ");
	free(temp);
	if (!msg)
		exit(1);
	temp = msg;
	msg = ft_strjoin(temp, p.cmd);
	free(temp);
	if (!msg)
		exit(1);
	temp = msg;
	msg = ft_strjoin(temp, "\n");
	free(temp);
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	handle_error(t_p p)
{
	if (p.path)
		p.e_m = strerror(errno);
	else if (p.argc >= 5)
		p.e_m = strerror(errno);
	write_e_msg(p);
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
