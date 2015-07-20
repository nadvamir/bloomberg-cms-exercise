#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#include "include/exceptions.h"
#include "include/parsers.h"
#include "include/Command.h"
#include "include/OrderStore.h"
#include "include/Message.h"

using namespace std;

int main(int argc, char **argv) {
    istream* stream;

    if (2 == argc && "base" == string(argv[1])) {
        stream = &cin;
    }
    else if (3 == argc && "ext1" == string(argv[1])) {
        return 1;
    }
    else if (3 == argc && "ext2" == string(argv[1])) {
        return 2;
    }
    else {
        cout << "USAGE: cms base | cms ext1 <port> "
                "| cms ext2 <port>" << endl;
        return 0;
    }

    OrderStorePtr store(new OrderStore());

    string line;
    while (getline(*stream, line)) {
        try {
            if (line.size() > 255) {
                throw InvalidMessage();
            }

            stringstream ss(line);
            CommandPtr cmd = parseMessage(ss);
            MessagePtr msg = (*cmd)(store);
            cout << *msg << endl;
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}

