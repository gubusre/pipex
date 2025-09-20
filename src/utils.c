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

static void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static char	*find_cmd(char *cmd, t_p p)
{
	char	*temp;
	char	*candidate;
	int		i;

	i = 0;
	p.path = ft_split(p.path_str, ':');
	if (!p.path)
		return (NULL);
	while (p.path[i])
	{
		temp = ft_strjoin(p.path[i], "/");
		candidate = ft_strjoin(temp, cmd);
		free(temp);
		if (access(candidate, X_OK) == 0)
			return (free_array(p.path), candidate);
		free(candidate);
		i++;
	}
	free_array(p.path);
	return (NULL);
}

void	exec_cmd(t_p p)
{
	char	**args;

	args = ft_split(p.cmd, ' ');
	if (!args)
	{
		p.e_m = "memory allocation failed";
		write_e_msg(p);
	}
	p.path_cmd = find_cmd(args[0], p);
	if (!p.path_cmd)
	{
		free_array(args);
		p.e_m = "command not found";
		write_e_msg(p);
	}
	if (execve(p.path_cmd, args, p.envp) == -1)
	{
		free_array(args);
		free(p.path);
		perror("zsh: execve");
	}
}

char	*ft_find_path(t_p p)
{
	char	*path_string;
	int		i;

	if (!p.cmd || !p.cmd[0])
		return (NULL);
	if (p.cmd[0] == '.' && p.cmd[1] == '/')
	{
		if (access(p.cmd, X_OK) != 0)
			return (NULL);
	}
	else
		return (NULL);
	i = 0;
	while (p.envp[i] && ft_strncmp(p.envp[i], "PATH=", 5) != 0)
		i++;
	if (!p.envp[i])
		return (NULL);
	path_string = p.envp[i] + 5;
	return (path_string);
}
