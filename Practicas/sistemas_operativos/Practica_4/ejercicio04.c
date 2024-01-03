#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s <arg>", argv[0]);
        return 1;
    }

    char current[PATH_MAX];
    getcwd(current, sizeof(current));

    char *pipePath = strcat(current, "/pipe");
    mkfifo(pipePath, 0777);

    int fd = open(pipePath, O_WRONLY);

    write(fd, argv[1], strlen(argv[1]));

    close(fd);

    return 0;
}