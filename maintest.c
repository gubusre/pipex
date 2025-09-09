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

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int	main(int argc, char* argv[])
{
	int     fd[2];
	pid_t   pid;
    char    buffer[1024];
    size_t  bytes_read;

    if (argc != 3 || errors(1, argv[1]) == -1 || errors(2, argv[2]) == -1)
    {
        printf("Uso: %s <archivo_entrada> <archivo_salida>\n", argv[0]);
        return (1);
    }
	if (pipe(fd) == -1)
    {
        printf("Error al crear pipe: %s\n", strerror(errno));
        return(1);
    }
	pid = fork();
    if (pid == -1)
    {
        printf("Error al crear fork: %s\n", strerror(errno));
        close(fd[0]);
        close(fd[1]);
        return(1);
    }
	if (pid != 0)
	{
        close(fd[0]);
        struct stat stat_fd1;
        fstat(fd[1], &stat_fd1);
		printf("Father pid %d\n", pid);
		printf("fd[0] %d\n", fd[0]);
		printf("STDIN_FILENO %d\n", STDIN_FILENO);
		printf("fd[1] %d (inode: %ld)\n", fd[1], stat_fd1.st_ino);

        int fd_in = open(argv[1], O_RDONLY);
        if (fd_in == -1)
        {
            printf("Error al abrir %s: %s\n", argv[1], strerror(errno));
            close(fd[1]);
            return 1;
        }
        while ((bytes_read = read(fd_in, buffer, sizeof(buffer))) > 0) 
        {
            if (write(fd[1], buffer, bytes_read) != bytes_read)
            {
                printf("Error al escribir en el pipe: %s\n", strerror(errno));
                close(fd_in);
                close(fd[1]);
                return 1;
            }
        }
        if (bytes_read == -1)
        {
            printf("Error al leer %s: %s\n", argv[1], strerror(errno));
            close(fd_in);
            close(fd[1]);
            return 1;
        }
        close(fd_in);
        close(fd[1]);
        wait(NULL);
    }
    else
    {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1)
        {
            printf("Error en dup2: %s\n", strerror(errno));
            close(fd[0]);
            return 1;
        }
        struct stat stat_fd0, stat_stdin;
        fstat(fd[0], &stat_fd0);
        fstat(STDIN_FILENO, &stat_stdin);
        printf("Son pid %d\n", pid);
        printf("fd[0] %d (inode: %ld)\n", fd[0], stat_fd0.st_ino);
        printf("STDIN_FILENO %d (inode: %ld)\n", STDIN_FILENO, stat_stdin.st_ino);
        printf("fd[1] %d\n", fd[1]);

        // Abrir el archivo de salida
        int fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1) {
            printf("Error al abrir %s: %s\n", argv[2], strerror(errno));
            close(fd[0]);
            return 1;
        }

        // Leer desde stdin (pipe) y escribir en el archivo de salida
        while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
            if (write(0, buffer, bytes_read) != bytes_read) {
                printf("Error al escribir en %s: %s\n", argv[2], strerror(errno));
                close(fd[0]);
                close(fd_out);
                return 1;
            }
        }
        if (bytes_read == -1) {
            printf("Error al leer desde el pipe: %s\n", strerror(errno));
            close(fd[0]);
            close(fd_out);
            return 1;
        }

        // Cerrar descriptores
        close(fd[0]);
        close(fd_out);
    }
	return(0);
}
// }
// int	main(int argc, char* argv[])
// {
// 	int	fd_in;
// 	int	fd_out;
// 	char	buffer[1024];
// 	size_t	bytes_read;

// 	if ((errors(0, argv[1]) == -1) || errors(1, argv[2]) == -1)
// 		return (1);
// 	fd_in = open(argv[1], O_RDONLY);
// 	if (fd_in == -1)
// 		printf("Error to open %s: %s\n", argv[1], strerror(errno));
// 	fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd_out == -1)
// 	{
// 		printf("Error to open %s: %s\n", argv[2], strerror(errno));
// 		close(fd_in);
// 		return (1);
// 	}
// 	while ((bytes_read = read(fd_in, buffer, sizeof(buffer))) > 0)
// 	{
// 		if (write(fd_out, buffer, bytes_read) != bytes_read)
// 		{
// 			printf("Error al escribir en %s: %s\n", argv[2], strerror(errno));
// 			close(fd_in);
// 			close(fd_out);
// 			return (1);
// 		}
// 	}
// 	if (bytes_read == -1)
// 	{
// 		printf("Error on read %s: %s\n", argv[1], strerror(errno));
// 		close(fd_in);
// 		close(fd_out);
// 		return (1);
// 	}
// 	close(fd_in);
// 	close(fd_out);
// 	return (0);
// }
