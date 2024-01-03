// sigqueue
// sigaction
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

char *exe;
int borrado = 0;

void handler(int signal)
{
    sigset_t mask, prev_mask;
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, &prev_mask);

    if (SIGALRM == signal && borrado)
    {
        char cwd[1024];
        getcwd(cwd, 1024);

        char **args = (char *[]){exe, "-f"};

        unlink(exe);
        execvp("rm", args);
    }
    if (SIGUSR1 == signal)
    {
        printf("Se ha evitado el borrado del ejecutable\n");
        borrado = 1;
    }
    sigprocmask(SIG_SETMASK, &prev_mask, NULL);
}

int main(int argc, char **argv)
{

    exe = argv[0];

    printf("PID del programa: %d\n", getpid());

    struct sigaction action;

    sigaction(SIGALRM, NULL, &action);
    sigaction(SIGUSR1, NULL, &action);
    action.sa_handler = handler;
    sigaction(SIGALRM, &action, NULL);
    sigaction(SIGUSR1, &action, NULL);
    printf("En 10 segundos se eliminará el ejecutable\n");
    sigset_t sigset_pending;
    alarm(10);

    sigsuspend(&sigset_pending);

    return 0;
}