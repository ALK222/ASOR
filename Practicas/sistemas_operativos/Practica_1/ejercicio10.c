#include <stdio.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

    __uid_t rId = getuid();
    __uid_t eId = geteuid();

    struct passwd *usuario;
    usuario = getpwuid(rId);

    printf("Nombre de usuario: %s\n", usuario->pw_name);
    printf("Nombre dir. home: %s\n", usuario->pw_dir);
    printf("Descripcion: %s\n", usuario->pw_gecos);

    // free(*usuario);

    return 0;
}
