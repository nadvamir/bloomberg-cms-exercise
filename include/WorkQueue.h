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
public:
    WorkQueue() {
        pthread_mutexattr_t attr;

        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&mutex_, &attr);

        pthread_cond_t cvar = PTHREAD_COND_INITIALIZER; 
        nonEmpty_ = cvar;
    }

    ~WorkQueue() {
        pthread_mutex_destroy(&mutex_);
    }

    T pop() {
        Lock lock(&mutex_);

        while (queue_.empty()) {
            pthread_cond_wait(&nonEmpty_, &mutex_);
        }

        T item = queue_.front();
        queue.pop();

        return item;
    }

    void push(const T& item) {
        Lock lock(&mutex_);
        queue_.push(item);
        pthread_cond_signal(&nonEmpty_);
    }
};

#endif
