#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

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

    bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

    freeaddrinfo(res);

    struct sockaddr_storage client;
    socklen_t client_len = sizeof(client);

    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    char buffer[256];
    ssize_t bytes;
    int client_sd;

    listen(sd, 5);
    client_sd = accept(sd, (struct sockaddr *) &client, &client_len);

    getnameinfo((struct sockaddr *) &client, client_len, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

    printf("Conection from %s:%s\n", host,serv);

    while(1)
    {
        bytes = recv(client_sd,buffer,255,0);
        buffer[bytes] = '\0';

        if(buffer[0]=='q' && bytes==2)
        {
            printf("Conection ended\n");
            break;
        }
        send(client_sd, buffer, bytes, 0);
    }
    close(client_sd);
    close(sd);

    return 0;
}