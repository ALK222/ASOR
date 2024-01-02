#include <fcntl.h>

int main()
{

    mode_t mode = 00645;

    int x = open("./ejercicio5_prueba", O_WRONLY | O_CREAT, mode);
    return 0;
}
