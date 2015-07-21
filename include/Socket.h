#ifndef SOCKET_H
#define SOCKET_H

class Socket {
    int fd_;
public:
    Socket(int port);

    int fd() const { return fd_; }

    int accept();
};

#endif
