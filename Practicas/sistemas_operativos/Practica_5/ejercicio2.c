#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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
    int parar = 0;

    while(parar == 0)
    {
        ssize_t bytes = recvfrom(udpServer, buf, 2, 0, (struct sockaddr *) &client_addr, &client_addrlen);
        buf[1] = '\0';

        getnameinfo((struct addr*) &client_addr, client_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

        printf("Recibi %ld bytes de %s(%s)\n", bytes, host, serv);

        time_t tiempo = time(NULL);
        struct tm * tm = localtime(&tiempo);

        size_t max;
        char s[50];

        ssize_t bytesT;
        
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
                parar = 1;
                break;
            default:
                sendto(udpServer, "Comando no soportado...\0", 26, 0, (struct sockaddr *) &client_addr, client_addrlen);
        }
    }

    return 0;
}