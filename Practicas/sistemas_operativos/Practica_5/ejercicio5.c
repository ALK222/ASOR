#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_CHILDREN 5

pid_t children[MAX_CHILDREN];
int parar = 0;

void handle_sigterm(int signum)
{
    printf("Terminando proceso %d\n", getpid());
    kill(getpid(), SIGTERM);
    exit(0);
}


int main(int argc, char **argv)
{

if(argc!= 3)
    {
        printf("ussage: %s <ip> <port>", argv[0]);
        return -1;
    }
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    struct addrinfo *res;

    if(getaddrinfo(argv[1], argv[2], &hints, &res)!= 0)
    {
        perror("getaddrinfo");
        return -1;
    }

    int udpServer = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    bind(udpServer, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

    printf("Servidor creado\n");
    
    char buf[2];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    struct sockaddr_storage client_addr;

    socklen_t client_addrlen = sizeof(struct sockaddr_storage);

    int i = 0;
    int status;

    pid_t pid;
    pid = fork();
    for(i = 1; i < MAX_CHILDREN; ++i)
    {
        if(pid != 0)
        {
            pid = fork();
        }

    }
        if(pid == 0)
        {
            printf("pid %d\n", getpid());
            sleep(0.5);
            signal(SIGTERM, handle_sigterm);

            fd_set readset;
            int result = -1;

            printf("Prueba\n");
            sleep(0.5);

            while(parar == 0)
            {

                do 
                {
                    FD_ZERO(&readset);
                    FD_SET(0,&readset);
                    FD_SET(udpServer, &readset);

                    result = select(udpServer + 1, &readset, NULL, NULL, NULL);
                } while(result == -1);
                
                time_t tiempo = time(NULL);
                struct tm * tm = localtime(&tiempo);

                char s[50];
                size_t max = sizeof(s);


                ssize_t bytesT;

                if(FD_ISSET(udpServer, &readset)) {
                    ssize_t bytes = recvfrom(udpServer, buf, 2, 0, (struct sockaddr *) &client_addr, &client_addrlen);
                    buf[1] = '\0';

                    getnameinfo((struct sockaddr*) &client_addr, client_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

                    printf("Recibi %ld bytes de %s(%s) con pid %d\n", bytes, host, serv,getpid());

                
                    switch (buf[0])
                    {
                        case 't':
                            bytesT = strftime(s, max, "%I:%M:%S %p", tm);
                            s[bytesT] ='\0';

                            sendto(udpServer, s, bytesT, 0, (struct sockaddr *) &client_addr, client_addrlen);
                            break;
                        case 'd':
                            bytesT = strftime(s, max, "%A %d - %B - %Y", tm);
                            s[bytesT] = '\0';

                            sendto(udpServer, s, bytesT, 0, (struct sockaddr *) &client_addr, client_addrlen);
                            break;
                        case 'q':
                            sendto(udpServer, "Comando de finalizacion recibido, saliendo...\0", 47, 0, (struct sockaddr *) &client_addr, client_addrlen);
                            kill(0,SIGTERM);
                            parar = 1;
                            break;
                        default:
                            sendto(udpServer, "Comando no soportado...\0", 26, 0, (struct sockaddr *) &client_addr, client_addrlen);
                    }
                }
                else 
                {
                    read(0, buf, 2);
                    buf[1] = '\0';
                    printf("Recibí %i byte(s) de consola con pid %d\n", 2, getpid());

                    switch(buf[0])
                    {
                        case 't':
                            bytesT = strftime(s,max, "%I:%M:%S %p", tm);
                            s[bytesT] = '\0';
                            printf("%s\n", s);
                            break;
                        case 'd':
                            bytesT = strftime(s,max, "%A %d - %B - %Y", tm);
                            s[bytesT] = '\0';
                            printf("%s\n",s);
                            break;
                        case 'q':
                            parar = 1;
                            printf("Comando de finalizacion recibido, saliendo...\n");
                            sleep(0.5);
                            kill(0,SIGTERM);
                            break;
                        default:
                            printf("comando no soportado...\n");
                            break;
                    }
                    sleep(0.5);
                }
            }
        }
        else 
        {
            pid = wait(&status);
        }
    
    
    return 0;
}