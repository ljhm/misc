//server.c
//$ gcc server.c -o server.out && ./server.out 192.168.1.64 10240

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
    int listenfd, acceptfd; //epfd
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

    listenfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listenfd == -1)
    {
        PRINT_LOG("socket: %s", strerror(errno));
        return 1;
    }

    ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(sockopt));
    if (ret == -1)
    {
        PRINT_LOG("setsockopt: %s", strerror(errno));
        return 1;
    }

    ret = bind(listenfd, result->ai_addr, result->ai_addrlen);
    if (ret == -1)
    {
        PRINT_LOG("bind: %s", strerror(errno));
        return 1;
    }

    freeaddrinfo(result);

    ret = listen(listenfd, SOMAXCONN);
    if (ret == -1)
    {
        PRINT_LOG("listen: %s", strerror(errno));
        return 1;
    }

    while (1)
    {
        acceptfd = accept(listenfd, NULL, NULL);
        if (acceptfd == -1)
        {
            PRINT_LOG("accept: %s", strerror(errno));
            return 1;
        }

        //send / recv
        char buf[1024];
        char *msg = "Hello222";

        ret = recv(acceptfd, buf, sizeof(buf) - 1, 0);
        buf[ret] = 0;
        PRINT_LOG("recv: %s", buf);

        ret = send(acceptfd, msg, strlen(msg), 0);
        //send / recv

        ret = close(acceptfd);
        if (ret == -1)
        {
            PRINT_LOG("close: %s", strerror(errno));
            return 1;
        }
    }

    ret = close(listenfd);
    if (ret == -1)
    {
        PRINT_LOG("close: %s", strerror(errno));
        return 1;
    }

    return 0;
}
