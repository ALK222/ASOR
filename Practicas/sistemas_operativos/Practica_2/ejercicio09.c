#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    struct stat sb;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (stat(argv[1], &sb) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("File: %s\n", argv[1]);

    switch (sb.st_mode & __S_IFMT)
    {
    case __S_IFBLK:
        printf("block device\n");
        break;
    case __S_IFCHR:
        printf("character device\n");
        break;
    case __S_IFDIR:
        printf("directory\n");
        break;
    case __S_IFIFO:
        printf("FIFO/pipe\n");
        break;
    case __S_IFLNK:
        printf("symlink\n");
        break;
    case __S_IFREG:
        printf("regular file\n");
        break;
    case __S_IFSOCK:
        printf("socket\n");
        break;
    default:
        printf("unknown?\n");
        break;
    }

    uintmax_t menor = minor(sb.st_dev);

    uintmax_t mayor = major(sb.st_dev);
    printf("Dispositivo: %i,%i ", mayor, menor);
    printf("I-nodo: %ld\n", (long)sb.st_ino);

    printf("Acceso:         %s", ctime(&sb.st_atime));

    exit(EXIT_SUCCESS);
}
