#include <stdio.h>
#include <unistd.h>

int main()
{

    __uid_t rId = getuid();
    __uid_t eId = geteuid();

    printf("Id real: %d\n", rId);
    printf("Id efectivo: %d\n", eId);

    return 0;
}
