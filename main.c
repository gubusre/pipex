#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int fd[2];
    pid_t pid1, pid2;
    int fd_in, fd_out;

    // Verificar argumentos: <infile> <cmd1> <cmd2> <outfile>
    if (argc != 5) {
        printf("Uso: %s <infile> <cmd1> <cmd2> <outfile>\n", argv[0]);
        return 1;
    }

    // Crear el pipe
    if (pipe(fd) == -1) {
        printf("Error al crear pipe: %s\n", strerror(errno));
        return 1;
    }

    // Crear primer hijo (cmd1)
    pid1 = fork();
    if (pid1 == -1) {
        printf("Error al crear primer fork: %s\n", strerror(errno));
        close(fd[0]);
        close(fd[1]);
        return 1;
    }

    if (pid1 == 0) { // Primer hijo (cmd1)
        // Cerrar el extremo de lectura del pipe
        close(fd[0]);

        // Redirigir entrada desde infile
        fd_in = open(argv[1], O_RDONLY);
        if (fd_in == -1) {
            printf("Error al abrir %s: %s\n", argv[1], strerror(errno));
            close(fd[1]);
            return 1;
        }
        if (dup2(fd_in, STDIN_FILENO) == -1) {
            printf("Error en dup2 para stdin: %s\n", strerror(errno));
            close(fd_in);
            close(fd[1]);
            return 1;
        }
        close(fd_in);

        // Redirigir salida al pipe
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            printf("Error en dup2 para stdout: %s\n", strerror(errno));
            close(fd[1]);
            return 1;
        }
        close(fd[1]);

        // Ejecutar cmd1 (por ejemplo, "ls -l")
        char *cmd1_args[] = {"/bin/sh", "-c", argv[2], NULL};
        execve("/bin/sh", cmd1_args, NULL);
        printf("Error al ejecutar %s: %s\n", argv[2], strerror(errno)); // Si execve falla
        return 1;
    }

    // Crear segundo hijo (cmd2)
    pid2 = fork();
    if (pid2 == -1) {
        printf("Error al crear segundo fork: %s\n", strerror(errno));
        close(fd[0]);
        close(fd[1]);
        return 1;
    }

    if (pid2 == 0) { // Segundo hijo (cmd2)
        // Cerrar el extremo de escritura del pipe
        close(fd[1]);

        // Redirigir entrada desde el pipe
        if (dup2(fd[0], STDIN_FILENO) == -1) {
            printf("Error en dup2 para stdin: %s\n", strerror(errno));
            close(fd[0]);
            return 1;
        }
        close(fd[0]);

        // Redirigir salida a outfile
        fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1) {
            printf("Error al abrir %s: %s\n", argv[4], strerror(errno));
            return 1;
        }
        if (dup2(fd_out, STDOUT_FILENO) == -1) {
            printf("Error en dup2 para stdout: %s\n", strerror(errno));
            close(fd_out);
            return 1;
        }
        close(fd_out);

        // Ejecutar cmd2 (por ejemplo, "wc -l")
        char *cmd2_args[] = {"/bin/sh", "-c", argv[3], NULL};
        execve("/bin/sh", cmd2_args, NULL);
        printf("Error al ejecutar %s: %s\n", argv[3], strerror(errno)); // Si execve falla
        return 1;
    }

    // Proceso padre
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0); // Esperar al primer hijo
    waitpid(pid2, NULL, 0); // Esperar al segundo hijo

    return 0;
}