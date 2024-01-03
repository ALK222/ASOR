#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: %s \"<command> <arg1>..<argn>\"\n", argv[0]);
        return -1;
    }

    char *program = argv[1];

    system(program);

    printf("El comando terminó de ejecutarse\n");
    return 0;
}