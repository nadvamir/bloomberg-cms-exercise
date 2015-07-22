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
#include "include/WorkQueue.h"
#include "include/ThreadPool.h"

const int NUM_THREADS = 10;

using namespace std;

typedef WorkQueue<ChanelPtr> Queue;
typedef SharedPtr<Queue> QueuePtr;

struct ThreadData {
    QueuePtr q;
    OrderStorePtr store;
};
struct ProducerData {
    QueuePtr q;
    SocketPtr socket;
    ProducerData(QueuePtr _q, SocketPtr _s) : q(_q), socket(_s) {}
};

typedef SharedPtr<ProducerData> PDataPtr;
typedef SharedPtr<ThreadPool> ThreadPoolPtr;

// pthread wrappers
void* worker(void*);
void* producer(void*);
// consumes connections put on queue by the producer
void consumeConnections(QueuePtr& q, OrderStorePtr& store);
// services the connection until it is closed
void processConnection(ChanelPtr& chanel, OrderStorePtr& store);

int main(int argc, char **argv) {
    QueuePtr workQueue(new Queue());
    OrderStorePtr store(new OrderStore());
    SocketPtr socket;
    ThreadPoolPtr tpool;
    ThreadPoolPtr producerThread;
    ThreadData td = { workQueue, store };

    if (2 == argc && "base" == string(argv[1])) {
        // this thread does all producing work, so:
        producerThread = ThreadPoolPtr(new ThreadPool());
        workQueue->push(ChanelPtr(new StreamChanel(cin, cout)));

        tpool = ThreadPoolPtr(new ThreadPool(1, worker, &td));

        cout << "CMS<GO> 'stdin' edition ready!" << endl;
    }
    else if (3 == argc && "ext1" == string(argv[1])) {
        stringstream ss(argv[2]);
        int port; ss >> port;

        socket = SocketPtr(new Socket(port));

        tpool = ThreadPoolPtr(new ThreadPool(1, worker, &td));

        cout << "CMS<GO> 'single request for socket on port "
             << port << "' edition ready!" << endl;

        // this thread does all producing work, so:
        producerThread = ThreadPoolPtr(new ThreadPool());
        workQueue->push(ChanelPtr(
            new NetworkChanel(socket->accept())));
    }
    else if (3 == argc && "ext2" == string(argv[1])) {
        // can't reuse ext1 code in any non-overkill fashion
        // or I will break single connection semantics
        stringstream ss(argv[2]);
        int port; ss >> port;

        socket = SocketPtr(new Socket(port));

        tpool = ThreadPoolPtr(
            new ThreadPool(NUM_THREADS, worker, &td));

        PDataPtr pDataPtr(new ProducerData(workQueue, socket));
        producerThread = ThreadPoolPtr(
            new ThreadPool(1, producer, &pDataPtr));

        cout << "CMS<GO> 'requests for socket on port "
             << port << "' edition ready!" << endl;
    }
    else {
        cout << "USAGE: cms base | cms ext1 <port> "
                "| cms ext2 <port>" << endl;
        return 0;
    }

    tpool->join();
    producerThread->cancel();

    return 0;
}

void* worker(void* data) {
    ThreadData* td = reinterpret_cast<ThreadData*>(data);
    consumeConnections(td->q, td->store);
    return NULL;
}

void* producer(void* data) {
    PDataPtr td = *reinterpret_cast<PDataPtr*>(data);
    while (true) {
        td->q->push(ChanelPtr(
            new NetworkChanel(td->socket->accept())));
    }
    return NULL;
}

void consumeConnections(QueuePtr& q, OrderStorePtr& store) {
    ChanelPtr chanel;
    while(q->pop(chanel)) {
        processConnection(chanel, store);
        q->reportDone();
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
