/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:02:43 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/18 12:34:25 by gubusque         ###   ########.fr       */
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
	char	**args;
	char	*msg;
	char	*cmd;
	int		fd[2];
	int		pipex;
	int		argc;
	int		infile;
	int		outfile;
	int		pid;
	int		i;
	int		norminette;
}	t_p;

void	exec_cmd(t_p p);
char	*find_path(char *cmd, char **envp);
void	handle_error(t_p p);
#endif
