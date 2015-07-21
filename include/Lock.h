#ifndef LOCK_H
#define LOCK_H

#include <pthread.h>

class Lock {
    pthread_mutex_t* mutex_;
public:
    Lock(pthread_mutex_t* mutex) : mutex_(mutex) {
        pthread_mutex_lock(mutex_);
    }

    ~Lock() {
        pthread_mutex_unlock(mutex_);
    }
};

#endif
