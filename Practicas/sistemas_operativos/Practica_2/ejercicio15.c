#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s <file>\n", argv[0]);
        return -1;
    }

    int file = open(argv[1], O_RDWR, 0645);

    if (file == -1)
    {
        perror("open");
        return -1;
    }

    int lock = lockf(file, F_LOCK, 0);

    if (lock == -1)
    {
        perror("lockf");
        return -1;
    }

    printf("Locked\n");

    sleep(10);
    lock = lockf(file, F_ULOCK, 0);
    printf("Unlocked\n");
    sleep(10);

    return 0;
}