/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:15:52 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/17 21:36:07 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(t_p p)
{
	if (p.argc == 1)
	{
		write(2, "zsh: parse error near `\\n'\n", 27);
		exit(1);
	}
	if (p.argv[1][0] == '|' && p.argv[1][1] == '|')
	{
		write(2, "zsh: parse error near `||'\n", 28);
		exit(1);
	}
	if (p.argv[1][0] == '|' && p.argv[1][1] != '|')
	{
		write(2, "zsh: parse error near `|'\n", 27);
		exit(1);
	}
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

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	path = find_path(args[0], envp);
	if (!path)
	{
		free_array(args);
		perror("Command not found");
		exit(127);
	}
	execve(path, args, envp);
	perror("execve");
	exit(1);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_str;
	char	*candidate;
	int		i;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path_str = envp[i] + 5;
	paths = ft_split(path_str, ':');
	i = 0;
	while (paths[i])
	{
		candidate = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (access(candidate, X_OK) == 0)
			return (free_array(paths), candidate);
		free(candidate);
		i++;
	}
	return (free_array(paths), NULL);
}
