#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s <fichero>\n", argv[0]);
        return -1;
    }

    int file = open(argv[1], O_CREAT | O_WRONLY, 0645);

    if (file == -1)
    {
        perror("open");
        return -1;
    }
    dup2(file, STDOUT_FILENO);
    dup2(file, STDERR_FILENO);

    perror("A");

    for (int i = 0; i < 10; ++i)
    {
        printf("%d\n", i);
    }

    return 0;
}