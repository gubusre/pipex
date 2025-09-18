/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gubusque <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/09/08 11:15:52 by gubusque		  #+#	#+#			 */
/*   Updated: 2025/09/18 18:57:25 by gubusque         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

char	*build_e_msg(const char *prefix, const char *error, const char *cmd)
{
	char	*msg;
	char	*temp;
	char	*cmd_s;

	if (cmd && cmd[0] != '\0')
		cmd_s = (char *)cmd;
	else
		cmd_s = "unknow";
	msg = ft_strjoin(prefix, error);
	if (!msg)
		return (NULL);
	temp = msg;
	msg = ft_strjoin(temp, ": ");
	free(temp);
	if (!msg)
		return (NULL);
	temp = msg;
	msg = ft_strjoin(temp, cmd);
	free(temp);
	if (!msg)
		
Hoy
Ayer
Esta semana

Hoy
Ayer
Esta semana
return (NULL);
	temp = msg;
	msg = ft_strjoin(temp, "\n");
	free(temp);
	return (msg);
}

void	handle_error(t_p p)
{
	char	*error_str;
	char	*error_msg;

	if (p.path)
	{
		if (errno == EACCES)
			error_str = "permission denied";
		else
			error_str = strerror(errno);
	}
	else
		error_str = strerror(errno);
	error_msg = build_e_msg("zsh: ", error_str, p.cmd);
	write(2, error_msg, ft_strlen(error_msg));
	free(error_msg);
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

void	exec_cmd(t_p p)
{
	char	*e_msg;

	p.args = ft_split(p.cmd, ' ');
	if (!p.args)
	{
		e_msg = build_e_msg("zsh: ", "memory allocation failed: ", p.cmd);
		write(2, e_msg, ft_strlen(e_msg));
		free(e_msg);
		exit(1);
	}
	p.path = find_path(p.args[0], p.envp);
	if (!p.path)
	{
		free_array(p.args);
		e_msg = build_e_msg("zsh: ", "command not found: ", p.cmd);
		write(2, e_msg, ft_strlen(e_msg));
		free(e_msg);
		exit(1);
	}
	if (execve(p.path, p.args, p.envp) == -1)
	{
		free_array(p.args);
		free(p.path);
		handle_error(p);
	}
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_str;
	char	*candidate;
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
		candidate = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (access(candidate, X_OK) == 0)
			return (free_array(paths), candidate);
		free(candidate);
		i++;
	}
	return (free_array(paths), NULL);
}
