#include <stdio.h>
#include <sys/utsname.h>

int main()
{

    struct utsname unameData;

    uname(&unameData);

    printf("Sys name: %s\n", unameData.sysname);
    printf("Node name: %s\n", unameData.nodename);
    printf("Release: %s\n", unameData.release);
    printf("Version: %s\n", unameData.version);
    printf("Machine: %s\n", unameData.machine);
    printf("Domain name: %s\n", unameData.__domainname);
    return 0;
}
