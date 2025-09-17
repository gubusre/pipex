/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:02:43 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/17 18:19:47 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_p
{
	char	**argv;
	char	**envp;
	char	*msg;
	char	*cmd;
	int		fd[2];
	int		pipex;
	int		argc;
	int		infile;
	int		outfile;
	int		pid;
	int		i;
}	t_p;

void	exec_cmd(char *cmd_str, char **envp);
char	*find_path(char *cmd, char **envp);
void	handle_error(t_p p);
#endif
