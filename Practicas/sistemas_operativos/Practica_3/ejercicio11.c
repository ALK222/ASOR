#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void setup(void)
{
    // creamos la variable de entorno
    setenv("SLEEP_SECS", "30", 1);
}

int main(int argc, char **argv)
{

    setup();

    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGTSTP);

    sigset_t old;
    sigprocmask(SIG_BLOCK, &sigset, &old);

    int sleepSecs = atoi(getenv("SLEEP_SECS"));

    printf("El proceso dormirá durante %d segundos\n", sleepSecs);
    sleep(sleepSecs);

    sigset_t sigset_pending;
    sigpending(&sigset_pending);

    sigset_t sigset_unmask;

    if (sigismember(&sigset_pending, SIGINT))
    {
        printf("Se recibió una señal SIGINT\n");
        sigaddset(&sigset_unmask, SIGINT);
    }
    if (sigismember(&sigset_pending, SIGTSTP))
    {
        printf("Se recibió una señal SIGTSTP\n");
        sigaddset(&sigset_unmask, SIGTSTP);
    }

    sigprocmask(SIG_UNBLOCK, &sigset_unmask, &old);

    return 0;
}