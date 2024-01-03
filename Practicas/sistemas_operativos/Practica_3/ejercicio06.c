#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/time.h>
#include <sys/resource.h>

void printParams(void)
{
    __pid_t pid = getpid();
    __pid_t ppid = getppid();

    __pid_t pgid = getpgid(pid);
    __pid_t sid = getsid(pid);

    struct rlimit lim;

    getrlimit(RLIMIT_NOFILE, &lim);

    char *wd = malloc(sizeof(char) * 100);
    getcwd(wd, 100);

    printf("PID: %d, PPID: %d, PGID: %d, PSID: %d\nNum max ficheros: %d, Directorio actual: %s\n", pid, ppid, pgid, sid, lim.rlim_cur, wd);

    free(wd);
}

int main()
{

    __pid_t pid;

    pid = fork();

    switch (pid)
    {
    case -1:
        perror("fork");
        exit(1);
    case 0: // demonio

        setsid();
        chdir("/tmp");
        printParams();
        break;
    default:
        break;
    }

    return 0;
}
