#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
    int i = 0;

    // El numero maximo de codigo de error es 133
    for (i; i < 134; i++)
    {
        printf("%s\n", strerror(i));
    }

    return 0;
}
