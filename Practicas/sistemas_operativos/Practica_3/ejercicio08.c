#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void printParams(char **argv)
{
    if (execvp(argv[1], argv + 1) == -1)
    {
        printf("Error(%i) -> %s\n", errno, strerror(errno));
    }
}

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        printf("usage: %s [<command> <arg1>..<argn>]\n", argv[0]);
        return -1;
    }

    __pid_t pid;

    pid = fork();

    switch (pid)
    {
    case -1:
        perror("fork");
        return -1;
    case 0: // demonio

        setsid();
        printf("%d\n", getpid());
        chdir("/tmp");
        int fdIn = open("/dev/null", O_CREAT | O_RDWR, 0777);
        int fdErr = open("daemon.err", O_CREAT | O_RDWR, 0777);
        int fdOut = open("daemon.out", O_CREAT | O_RDWR, 0777);
        dup2(fdOut, STDOUT_FILENO);
        dup2(fdErr, STDERR_FILENO);
        dup2(fdIn, STDIN_FILENO);
        printParams(argv);
        break;
    default:
        break;
    }

    return 0;
}
