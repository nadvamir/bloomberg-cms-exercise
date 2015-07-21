#ifndef SOCKET_H
#define SOCKET_H

#include "include/SharedPtr.h"

class Socket {
    int fd_;
public:
    Socket(int port);

    int fd() const { return fd_; }

    int accept();
};

typedef SharedPtr<Socket> SocketPtr;

#endif
