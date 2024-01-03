// sigqueue
// sigaction
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define NUM_SIGNALS_MAX 10

int contadorSIGINT = 0;
int contadorSIGTSTP = 0;

void contadores(int signal)
{
    sigset_t mask, prev_mask;
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, &prev_mask);

    if (signal == SIGINT)
    {
        contadorSIGINT++;
    }
    if (signal == SIGTSTP)
    {
        contadorSIGTSTP++;
        // printf("%d\n", contadorSIGTSTP);
    }
    sigprocmask(SIG_SETMASK, &prev_mask, NULL);
}

int main(int argc, char **argv)
{
    struct sigaction action;

    sigaction(SIGINT, NULL, &action);
    sigaction(SIGTSTP, NULL, &action);
    action.sa_handler = contadores;
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTSTP, &action, NULL);

    sigset_t sigset;

    while (contadorSIGINT + contadorSIGTSTP < NUM_SIGNALS_MAX)
        sigsuspend(&sigset);

    printf("\nSeñales capturadas:\n\t%d SIGINT\n\t%d SIGTSTP\nTotal:%d\n", contadorSIGINT, contadorSIGTSTP, contadorSIGINT + contadorSIGTSTP);

    return 0;
}