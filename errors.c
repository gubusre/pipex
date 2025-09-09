/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:15:52 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/08 17:57:11 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

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
