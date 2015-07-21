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
    WorkQueue() : state_(Idle), numWorkers_(0) {
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

    bool pop(T& item) {
        Lock lock(&mutex_);

        while (queue_.empty()) {
            if (state_ == Closing) {
                return false;
            }
            pthread_cond_wait(&nonEmpty_, &mutex_);
        }

        item = queue_.front();
        queue_.pop();

        if (state_ == Idle) {
            state_ = Working;
        }
        
        ++numWorkers_;
        return true;
    }

    void push(const T& item) {
        Lock lock(&mutex_);
        queue_.push(item);
        pthread_cond_signal(&nonEmpty_);
    }

    void reportDone() {
        Lock lock(&mutex_);
        if (0 == --numWorkers_ && queue_.empty()) {
            state_ = Closing;
            pthread_cond_broadcast(&nonEmpty_);
        }
    }
};

#endif
