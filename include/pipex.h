/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:02:43 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/18 19:29:00 by gubusque         ###   ########.fr       */
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
	char	*path;
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

char	*find_path(char *cmd, char **envp);
char	*build_e_msg(const char *prefix, const char *error, const char *cmd);
int	ft_first_child(t_p p);
int	ft_childs(t_p p);
int	ft_last_child(t_p p);
void	exec_cmd(t_p p);
void	handle_error(t_p p);
void	free_array(char **arr);
#endif
