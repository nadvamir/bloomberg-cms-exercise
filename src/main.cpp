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
#include "include/LineReader.h"
#include "include/SharedPtr.h"

using namespace std;

typedef queue<LineReaderPtr> WorkQueue;
typedef SharedPtr<WorkQueue> QueuePtr;

void processRequests(QueuePtr& q, OrderStorePtr& store);

int main(int argc, char **argv) {
    QueuePtr workQueue(new WorkQueue());

    if (2 == argc && "base" == string(argv[1])) {
        workQueue->push(LineReaderPtr(new StreamLineReader(cin)));
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

    processRequests(workQueue, store);

    return 0;
}

void processRequests(QueuePtr& q, OrderStorePtr& store) {
    while (!q->empty()) {
        LineReaderPtr reader = q->front();
        q->pop();

        string line;
        while (reader->getline(line)) {
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
    }
}
