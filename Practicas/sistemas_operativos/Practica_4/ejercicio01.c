#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pipefd[2]; // file descriptor
    char buf;
    pid_t cpid;

    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s comando1 argumento1 comando2 argumento 2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    {                     /* Child reads from pipe */
        close(pipefd[1]); /* Close unused write end */

        dup2(pipefd[0], STDIN_FILENO);

        close(pipefd[0]);
        execlp(argv[3], argv[3], argv[4], NULL);
        _exit(EXIT_SUCCESS);
    }
    else
    {                     /* Parent writes argv[1] to pipe */
        close(pipefd[0]); /* Close unused read end */
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); /* Reader will see EOF */
        execlp(argv[1], argv[1], argv[2], NULL);

        // wait(NULL); /* Wait for child */
        exit(EXIT_SUCCESS);
    }
}
