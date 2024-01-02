#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("%s <archivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat sb;

    stat(argv[1], &sb);

    if ((sb.st_mode & __S_IFMT) == __S_IFREG)
    {

        char hard[64];
        char sym[64];

        strcpy(hard, argv[1]);
        strcpy(sym, argv[1]);

        strcat(hard, ".hard");
        strcat(sym, ".sym");

        symlink(argv[1], sym);
        link(argv[1], hard);
    }

    return 0;
}
