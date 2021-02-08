//server.cpp
//$ g++ server.cpp -lpthread -g -o server.out && ./server.out 192.168.1.64 10240

/*

Terminal 1:

$ ./server.out 192.168.1.64 10240
server.cpp:54 (workin) fd: 5, recv: Hello from client 111
server.cpp:64 (workout) fd: 6, send ..
server.cpp:54 (workin) fd: 6, recv: Hello from client 222
server.cpp:64 (workout) fd: 5, send ..
server.cpp:54 (workin) fd: 5, recv: Hello from client 111
server.cpp:64 (workout) fd: 6, send ..
server.cpp:54 (workin) fd: 6, recv: Hello from client 222
server.cpp:64 (workout) fd: 5, send ..

$

Terminal 2:

$ ./client.out 192.168.1.64 10240
client.c:62 (main) recv: Hello from server
$ ./client.out 192.168.1.64 10240
client.c:62 (main) recv: Hello from server
$

Terminal 3:

$ ./client2.out 192.168.1.64 10240
client2.c:62 (main) recv: Hello from server
$ ./client2.out 192.168.1.64 10240
client2.c:62 (main) recv: Hello from server
$

*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <thread>
#include "print_log.h"

void workin(int fd)
{
    char buf[1024];
    memset(buf, 0, sizeof(buf));

    int ret = recv(fd, buf, sizeof(buf) - 1, 0);
    //EAGAIN or EWOULDBLOCK

    buf[ret] = 0;
    PRINT_LOG("recv: %s, len: %d", buf, ret);
}

void workout(int fd)
{
    while (1)
    {
        char msg[10240*100];
        memset(msg, '*', sizeof(msg));
        msg[sizeof(msg) - 1] = 0;

        int ret = send(fd, msg, strlen(msg), 0);
        //EAGAIN or EWOULDBLOCK

        if (ret == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                break;
            }
            else
            {
                close(fd);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    struct addrinfo hints, *result;
    const char *host = argv[1];
    const char *port = argv[2];
    int listenfd, acceptfd, epollfd;
    int sockopt = 1;
    int ret;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    struct epoll_event ev, events[10];

    //set up listening socket: socket(), bind(), listen()
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

    //epoll
    epollfd = epoll_create1(0);
    if (epollfd == -1)
    {
        PRINT_LOG("epoll_create1: %s", strerror(errno));
        return 1;
    }
    ev.events = EPOLLIN;
    ev.data.fd = listenfd;

    ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev);
    if (ret == -1)
    {
        PRINT_LOG("epoll_ctl: %s", strerror(errno));
        return 1;
    }

    while (1)
    {
        int cnt = epoll_wait(epollfd, events, sizeof(events) / sizeof(events[0]), -1);
        if (cnt == -1)
        {
            PRINT_LOG("epoll_wait: %s", strerror(errno));
            return 1;
        }

        for (int i = 0; i != cnt; i++)
        {
            if (events[i].data.fd == listenfd)
            {
                acceptfd = accept(listenfd, NULL, NULL);
                if (acceptfd == -1)
                {
                    PRINT_LOG("accept: %s", strerror(errno));
                    return 1;
                }

                //set socket non-block
                int flag = fcntl(acceptfd, F_GETFL);
                if (acceptfd == -1)
                {
                    PRINT_LOG("fcntl: %s", strerror(errno));
                    return 1;
                }
                flag |= O_NONBLOCK;
                flag = fcntl(acceptfd, F_SETFL, flag);
                if (acceptfd == -1)
                {
                    PRINT_LOG("fcntl: %s", strerror(errno));
                    return 1;
                }

                //set edge trigger with read and write operations
                ev.events = EPOLLET | EPOLLIN | EPOLLOUT;
                ev.data.fd = acceptfd;
                ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, acceptfd, &ev);
                if (ret == -1)
                {
                    PRINT_LOG("epoll_ctl: %s", strerror(errno));
                    return 1;
                }
            }
            else if (events[i].events & (EPOLLHUP | EPOLLERR))
            {
                ret = close(events[i].data.fd);
                if (ret == -1)
                {
                    PRINT_LOG("close: %s", strerror(errno));
                    return 1;
                }
            }
            else if (events[i].events & EPOLLIN)
            {
                int fd = events[i].data.fd;
                //PRINT_LOG("EPOLLIN on fd: %d", fd);
                std::thread(workin, fd).detach();
            }
            else if (events[i].events & EPOLLOUT)
            {
                int fd = events[i].data.fd;
                PRINT_LOG("EPOLLOUT on fd: %d", fd);
                std::thread(workout, fd).detach();
            }
            else
            {
                PRINT_LOG("Unknown events: %u", events[i].events);
            }
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
