#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Long. max. argumentos: %d\n", sysconf(_SC_ARG_MAX));
    printf("Num. max. hijos: %d\n", sysconf(_SC_CHILD_MAX));
    printf("Num. max. ficheros abiertos: %d\n", sysconf(_SC_OPEN_MAX));

    return 0;
}
