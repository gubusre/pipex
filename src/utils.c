/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gubusque <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/09/08 11:15:52 by gubusque		  #+#	#+#			 */
/*   Updated: 2025/09/18 20:50:52 by gubusque         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

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

static void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_str;
	char	*candidate;
	char	*temp;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
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
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		candidate = ft_strjoin(temp, cmd);
		free(temp);
		if (access(candidate, X_OK) == 0)
			return (free_array(paths), candidate);
		free(candidate);
		i++;
	}
	return (free_array(paths), NULL);
}

void	exec_cmd(t_p p)
{
	p.args = ft_split(p.cmd, ' ');
	if (!p.args)
	{
		p.e_m = "memory allocation failed";
		write_e_msg(p);
	}
	p.path = find_path(p.args[0], p.envp);
	if (!p.path)
	{
		free_array(p.args);
		p.e_m = "command not found";
		write_e_msg(p);
	}
	if (execve(p.path, p.args, p.envp) == -1)
	{
		free_array(p.args);
		free(p.path);
		perror("execve");
	}
}
