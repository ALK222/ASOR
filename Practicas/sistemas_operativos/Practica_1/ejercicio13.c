#include <stdio.h>
#include <sys/time.h>

int main()
{

    struct timeval after;

    struct timeval before;

    gettimeofday(&before, NULL);

    int i = 0;

    for (i; i < 1000000; ++i)
        ;

    gettimeofday(&after, NULL);

    suseconds_t afterS = after.tv_usec;
    suseconds_t beforeS = before.tv_usec;

    printf("Microsegundos: %d\n", afterS - beforeS);

    return 0;
}
