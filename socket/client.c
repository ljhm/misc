//client.c
//$ gcc client.c -o client.out && ./client.out 192.168.1.64 10240

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "print_log.h"

int main(int argc, char *argv[])
{
    struct addrinfo hints, *result;
    const char *host = argv[1];
    const char *port = argv[2];
    int sfd;
    int sockopt = 1;
    int ret;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;

    if (argc != 3)
    {
        PRINT_LOG("Usage: %s <host> <port>", argv[0]);
        return 1;
    }

    ret = getaddrinfo(host, port, &hints, &result);
    if (ret != 0)
    {
        PRINT_LOG("getaddrinfo: %s", gai_strerror(ret));
        return 1;
    }

    sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sfd == -1)
    {
        PRINT_LOG("socket: %s", strerror(errno));
        return 1;
    }

    ret = connect(sfd, result->ai_addr, result->ai_addrlen);
    if (ret == -1)
    {
        PRINT_LOG("connect: %s", strerror(errno));
        return 1;
    }

    freeaddrinfo(result);

    //send / recv
    char buf[1024];
    char *msg = "Hello111";

    ret = send(sfd, msg, strlen(msg), 0);

    ret = recv(sfd, buf, sizeof(buf) - 1, 0);
    buf[ret] = 0;
    PRINT_LOG("recv: %s", buf);
    //send / recv

    ret = close(sfd);
    if (ret == -1)
    {
        PRINT_LOG("close: %s", strerror(errno));
        return 1;
    }

    return 0;
}
