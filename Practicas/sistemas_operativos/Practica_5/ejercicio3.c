#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv)
{

    if(argc!= 4)
    {
        printf("ussage: %s <ip> <port> <command>", argv[0]);
        return -1;
    } 

    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    struct addrinfo *res;

    if(getaddrinfo(argv[1], argv[2], &hints, &res) != 0)
    {
        perror("getaddrinfo");
        return -1;
    } 

    int cliente = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    char buf[2];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    struct sockaddr_storage client;
    socklen_t clientlen = sizeof(client);

    buf[0] = (char) argv[3][0];

    ssize_t send = sendto(cliente, buf, 2, 0, res->ai_addr, res->ai_addrlen);

    char s[50];
    ssize_t bytes = recvfrom(cliente, s, 50, 0, (struct sockaddr *) &client, &clientlen);
    s[bytes] = '\0';

    printf("%s\n", s);

    return 0;
}