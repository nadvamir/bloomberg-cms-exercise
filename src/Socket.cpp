#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdexcept>

#include "include/Socket.h"

using namespace std;

namespace {

const int BACKLOG = 10;

int create();
void bind(int fd, int port);

}

Socket::Socket(int port) {
    fd_ = create();
    bind(fd_, port);
    if (listen(fd_, BACKLOG) == -1) {
        throw runtime_error("failed to start listenning");
    }
}

int Socket::accept() {
    struct sockaddr_in cliaddr;
    socklen_t cliaddr_len = sizeof(cliaddr);

    int connfd = ::accept(fd_, (struct sockaddr *) &cliaddr,
                          &cliaddr_len);

    if (connfd == -1) {
        throw runtime_error("failed to accept a connection");
    }

    return connfd;
}

namespace {

int create() {
    int iSetOption = 1;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        throw runtime_error("unable to create socket");
    }

    // tell socket to release the connection after shutting down
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
               (char*)&iSetOption, sizeof(iSetOption));

    return fd;
}

void bind(int fd, int port) {
    struct sockaddr_in addr;

    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        throw runtime_error("unable to bind a "
                            "socket as a TCP/IP server");
    }
}

}
