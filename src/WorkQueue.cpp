#include "include/WorkQueue.h"

#include <pthread.h>
#include <queue>

#include "include/Lock.h"

template<class T>
WorkQueue<T>::WorkQueue() : state_(Idle), numWorkers_(0) {
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex_, &attr);

    pthread_cond_t cvar = PTHREAD_COND_INITIALIZER; 
    nonEmpty_ = cvar;
}

template<class T>
WorkQueue<T>::~WorkQueue() {
    pthread_mutex_destroy(&mutex_);
}

template<class T>
bool WorkQueue<T>::pop(T& item) {
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

template<class T>
void WorkQueue<T>::push(const T& item) {
    Lock lock(&mutex_);
    queue_.push(item);
    pthread_cond_signal(&nonEmpty_);
}

template<class T>
void WorkQueue<T>::reportDone() {
    Lock lock(&mutex_);
    if (0 == --numWorkers_ && queue_.empty()) {
        state_ = Closing;
        pthread_cond_broadcast(&nonEmpty_);
    }
}

