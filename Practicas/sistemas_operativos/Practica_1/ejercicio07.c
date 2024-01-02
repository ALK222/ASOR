#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Num. max. enlaces: %d\n", pathconf(".", _PC_LINK_MAX));
    printf("Tam. max. nombre ruta: %d\n", pathconf(".", _PC_PATH_MAX));
    printf("Tam. max. nombre fichero: %d\n", pathconf(".", _PC_NAME_MAX));

    return 0;
}
