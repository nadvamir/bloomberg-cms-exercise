#ifndef WORK_QUEUE_H
#define WORK_QUEUE_H

#include <queue>
#include <pthread.h>

#include "include/Lock.h"

template<class T>
class WorkQueue {
    typedef std::queue<T> InnerQueue;

    pthread_mutex_t mutex_;
    pthread_cond_t nonEmpty_;

    InnerQueue queue_;

    enum State { Idle, Working, Closing };
    State state_;
    int numWorkers_;
public:
    WorkQueue();

    ~WorkQueue();

    bool pop(T& item);

    void push(const T& item);

    void reportDone();
};

#endif
