#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main()
{
    int err;

    if (setuid(0) == -1)
    {
        err = errno;
        printf("%d\n", err);
        printf("%s\n", strerror(err));
    }

    return 1;
}
