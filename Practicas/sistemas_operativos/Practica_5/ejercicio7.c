#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if(argc!= 3)
    {
        printf("ussage: %s <ip> <port>", argv[0]);
        return -1;
    }
    struct addrinfo hints;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    memset(&hints, 0, sizeof(struct addrinfo));

    struct addrinfo *res;
    int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

    int sd = socket(res->ai_family, res->ai_socktype, 0);

    struct sockaddr_storage server;
    socklen_t server_len = sizeof(server);

    connect(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

    freeaddrinfo(res);

    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    getnameinfo((struct sockaddr *) &server, server_len, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

    char bufIn[256];
    char bufOut[256];

    // printf("Conection from %s:%s\n", host,serv);

    while(1)
    {
        ssize_t bytesOut = read(0,bufOut, 255);
        bufOut[bytesOut] = '\0';

        send(sd, bufOut, bytesOut, 0);

        if(bufOut[0] == 'q' && bytesOut == 2)
        {
            break;
        }

        ssize_t bytesIn = recv(sd, bufIn, 255, 0);
        bufIn[bytesIn] = '\0';
        printf("%s", bufIn);
    }
    close(sd);

    return 0;
}