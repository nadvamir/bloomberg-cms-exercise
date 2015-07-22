#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <functional>

typedef void* (*WORK_F)(void*);

// sharing same data piece is acceptable in our case,
// since we only share pointers which we don't modify directly
template<class Data>
class ThreadPool {
    std::vector<pthread_t> tpool;
public:
    ThreadPool(int size, WORK_F workF, Data* data) : tpool(size) {
        for (int i = 0; i < size; ++i) {
            if (pthread_create(&tpool[i], NULL, workF, data)) {
                throw std::runtime_error("Failed to create thread!");
            }
        }
    }
    
    void join() {
        std::for_each(tpool.begin(), tpool.end(),
                      std::bind2nd(std::ptr_fun(pthread_join), NULL));
    }
};

#endif
