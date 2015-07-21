#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <queue>

#include "include/exceptions.h"
#include "include/parsers.h"
#include "include/Command.h"
#include "include/OrderStore.h"
#include "include/Message.h"
#include "include/Chanel.h"
#include "include/Socket.h"
#include "include/SharedPtr.h"

using namespace std;

typedef queue<ChanelPtr> WorkQueue;
typedef SharedPtr<WorkQueue> QueuePtr;

void processConnections(QueuePtr& q, OrderStorePtr& store);
void processConnection(ChanelPtr& chanel, OrderStorePtr& store);

int main(int argc, char **argv) {
    QueuePtr workQueue(new WorkQueue());
    OrderStorePtr store(new OrderStore());
    SocketPtr socket;

    if (2 == argc && "base" == string(argv[1])) {
        workQueue->push(ChanelPtr(new StreamChanel(cin, cout)));
        cout << "CMS<GO> 'stdin' edition ready!" << endl;
    }
    else if (3 == argc && "ext1" == string(argv[1])) {
        stringstream ss(argv[2]);
        int port; ss >> port;

        socket = SocketPtr(new Socket(port));

        cout << "CMS<GO> 'single socket on port " << port
             << "' edition ready!" << endl;

        workQueue->push(ChanelPtr(
            new NetworkChanel(socket->accept())));
    }
    else if (3 == argc && "ext2" == string(argv[1])) {
        return 2;
    }
    else {
        cout << "USAGE: cms base | cms ext1 <port> "
                "| cms ext2 <port>" << endl;
        return 0;
    }

    processConnections(workQueue, store);

    return 0;
}

void processConnections(QueuePtr& q, OrderStorePtr& store) {
    while (!q->empty()) {
        ChanelPtr chanel = q->front();
        q->pop();

        processConnection(chanel, store);
    }
}

void processConnection(ChanelPtr& chanel, OrderStorePtr& store) {
    string line;
    while (chanel->getline(line)) {
        try {
            if (line.size() > MAX_LINE) {
                throw InvalidMessage();
            }

            stringstream ss(line);
            CommandPtr cmd = parseMessage(ss);
            MessagePtr msg = (*cmd)(store);

            stringstream output;
            output << *msg;

            chanel->putline(output.str());
        } catch (runtime_error& e) {
            chanel->putline(e.what());
        }
    }
}
