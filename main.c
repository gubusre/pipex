/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:22:55 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/08 18:20:23 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int	main(int argc, char* argv[])
{
	int	fd_in;
	int	fd_out;
	char	buffer[1024];
	size_t	bytes_read;

	if ((errors(0, argv[1]) == -1) || errors(1, argv[2]) == -1)
		return (1);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		printf("Error to open %s: %s\n", argv[1], strerror(errno));
	fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		printf("Error to open %s: %s\n", argv[2], strerror(errno));
		close(fd_in);
		return (1);
	}
	while ((bytes_read = read(fd_in, buffer, sizeof(buffer))) > 0)
	{
		if (write(fd_out, buffer, bytes_read) != bytes_read)
		{
			printf("Error al escribir en %s: %s\n", argv[2], strerror(errno));
			close(fd_in);
			close(fd_out);
			return (1);
		}
	}
	if (bytes_read == -1)
	{
		printf("Error on read %s: %s\n", argv[1], strerror(errno));
		close(fd_in);
		close(fd_out);
		return (1);
	}
	close(fd_in);
	close(fd_out);
	return (0);
}
