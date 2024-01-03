#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>

const int BUFFER_SIZE = 256;
const char *PIPE1_NAME = "pipe1";
const char *PIPE2_NAME = "pipe2";

int main(int argc, char **argv)
{

    mkfifo(PIPE1_NAME, 0644);
    mkfifo(PIPE2_NAME, 0644);
    char buffer[BUFFER_SIZE];

    int fd1 = open(PIPE1_NAME, O_RDONLY | O_NONBLOCK);
    int fd2 = open(PIPE2_NAME, O_RDONLY | O_NONBLOCK);

    int broken = 0;

    while (broken != -1)
    {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(fd1, &set);
        FD_SET(fd2, &set);

        broken = select(((fd1 > fd2) ? fd1 : fd2) + 1, &set, NULL, NULL, NULL);

        int curr;

        if (broken != -1)
        {
            if (FD_ISSET(fd1, &set))
            {
                curr = fd1;
            }
            if (FD_ISSET(fd2, &set))
            {
                curr = fd2;
            }
            int n_curr = (curr == fd1) ? 1 : 2;

            int bytesRead = BUFFER_SIZE;
            while (bytesRead == BUFFER_SIZE)
            {
                bytesRead = read(curr, buffer, BUFFER_SIZE);
                buffer[bytesRead] = '\0';
                printf("PIPE%i -> %s\n", n_curr, buffer);

                if (n_curr == 1)
                {
                    close(fd1);
                    fd1 = open(PIPE1_NAME, O_RDONLY | O_NONBLOCK);
                }
                if (n_curr == 2)
                {
                    close(fd2);
                    fd2 = open(PIPE2_NAME, O_RDONLY | O_NONBLOCK);
                }

                if (fd1 < 0 || fd2 < 0)
                {
                    printf("Error(%i) al reabrir pipe %i -> %s\n", errno, n_curr, strerror(errno));
                    broken = -1; // Si la reapertura de la pipe trada falla, rompemos el bucle para finalizar
                }
            }
        }
    }

    close(fd1);
    close(fd2);

    return 0;
}