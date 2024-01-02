#include <fcntl.h>
#include <sys/stat.h>

int main()
{

    mode_t mode = 0645;
    mode_t mask = 0027;

    umask(mask);
    int x = open("./ejercicio7_prueba", O_WRONLY | O_CREAT, mode);
    return 0;
}
