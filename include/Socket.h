#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Socket {
    int fd_;
public:
    Socket(int port);

    int fd() const { return fd_; }

    int accept();
};

#endif
