#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdexcept>

#include "include/Chanel.h"

using namespace std;

NetworkChanel::~NetworkChanel() {
    close(connfd_);
}

bool NetworkChanel::getline(std::string& line) {
    int rcount = 0;
    const int BUF_LEN = MAX_LINE + 2; // so that we overflow
                                      // MAX_LINE with invalid
                                      // message
    char rdbuf[BUF_LEN];

    if ((rcount = read(connfd_, rdbuf, BUF_LEN - 1)) != 0) {
        if (rcount == -1) {
            throw runtime_error("Reading from the "
                                "connection failed");
        }
        rdbuf[rcount] = '\0';

        // for the sake of simplicity:
        // assume that the request always arrives in full
        // and that there can be no requests lumped together

        line = string(rdbuf);
        return true;
    }
    return false;
}

void NetworkChanel::putline(const std::string& line) {
    if (write(connfd_, line.c_str(), line.size()) == -1) {
        throw runtime_error("There was a problem in "
                            "sending the response");
    }
}

