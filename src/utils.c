/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:15:52 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/10 14:36:21 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	errors(int fd_type, const char* file)
{
	if (access(file, F_OK) == -1)
	{
		printf("Error: %s %s\n", file, strerror(errno));
		return (-1);
	}
	if ((fd_type == 0 && access(file, R_OK) == -1) ||
		(fd_type != 0 && access(file, W_OK) == -1)) 
	{
		printf("Error: %s %s\n", file, strerror(errno));
		return (-1);
	}
	return (0);
}

void free_array(char **arr)
{
    int i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

void exec_cmd(char *cmd_str, char **envp)
{
    char **args = ft_split(cmd_str, ' ');
    char *path;
    if (!args)
        exit(1);
    path = find_path(args[0], envp);
    if (!path)
    {
        free_array(args);
        perror("Command not found");
        exit(127);
    }
    execve(path, args, envp);
    free(path);
    free_array(args);
    perror("execve");
    exit(1);
}

char *find_path(char *cmd, char **envp)
{
    char **paths;
    char *path_str;
    char *candidate;
    char *tmp;
    int i;

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
        tmp = ft_strjoin(paths[i], "/");
        candidate = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(candidate, X_OK) == 0)
        {
            free_array(paths);
            return (candidate);
        }
        free(candidate);
        i++;
    }
    free_array(paths);
    return (NULL);
}

