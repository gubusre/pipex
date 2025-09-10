/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:05:38 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/10 14:16:34 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void free_array(char **arr)
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

int main(int argc, char **argv, char **envp)
{
    int fd_in;
    int fd_out;
    int pipefd[2];
    pid_t pid1;
    pid_t pid2;

    if (argc != 5)
    {
        write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
        exit(1);
    }
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0)
    {
        perror(argv[1]);
        exit(1);
    }
    fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_out < 0)
    {
        perror(argv[4]);
        close(fd_in);
        exit(1);
    }
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        close(fd_in);
        close(fd_out);
        exit(1);
    }
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid1 == 0)
    {
        close(pipefd[0]);
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        exec_cmd(argv[2], envp);
    }
    close(fd_in);
    close(pipefd[1]);
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid2 == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
        exec_cmd(argv[3], envp);
    }
    close(pipefd[0]);
    close(fd_out);
    return (0);
}
