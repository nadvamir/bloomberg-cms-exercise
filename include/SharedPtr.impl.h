#ifndef SHARED_PTR_IMPL_H
#define SHARED_PTR_IMPL_H
//-----------------------------------------------------------------
// not thread-safe non-inline functions
//-----------------------------------------------------------------
template<class T, bool TS>
SharedPtr<T>& SharedPtr<T, TS>::operator=(const SharedPtr<T>& sptr) {
    if (NULL != refCount_ && 0 == --(*refCount_)) {
        delete ptr_;
        delete refCount_;
    }

    ptr_ = sptr.ptr_;
    refCount_ = sptr.refCount_;
    if (NULL != refCount_) {
        ++(*refCount_);
    }

    return *this;
}

//-----------------------------------------------------------------
// thread-safe non-inline functions
//-----------------------------------------------------------------
template<class T>
SharedPtr<T, THREAD_SAFE>& SharedPtr<T, THREAD_SAFE>::operator=(
        const SharedPtr<T, THREAD_SAFE>& sptr) {
    if (NULL != refCount_) {
        {
            Lock lock(mutex_);
            --(*refCount_);
        }

        if (0 == *refCount_) { // won't go below 0, no lock needed
            delete ptr_;
            delete refCount_;
            pthread_mutex_destroy(mutex_);
            delete mutex_;
        }
    }

    ptr_ = sptr.ptr_;
    refCount_ = sptr.refCount_;
    mutex_ = sptr.mutex_;
    if (NULL != refCount_) {
        Lock lock(mutex_);
        ++(*refCount_);
    }

    return *this;
}

template <class T>
SharedPtr<T, THREAD_SAFE>::~SharedPtr() {
    if (NULL != refCount_) {
        {
            Lock lock(mutex_);
            --(*refCount_);
        }

        if (0 == *refCount_) {
            delete ptr_;
            delete refCount_;
            pthread_mutex_destroy(mutex_);
            delete mutex_;
        }
    }
}

template <class T>
template<class T_>
class SharedPtr<T, THREAD_SAFE>::LockingProxy {
public:
    LockingProxy(T_* pObj, pthread_mutex_t* mutex)
    : pointee_(pObj), mutex_(mutex) {
        pthread_mutex_lock(mutex_);
    }
    ~LockingProxy() {
        pthread_mutex_unlock(mutex_);
    }
    T_* operator->() const { return pointee_; }
private:
    T_* pointee_;
    pthread_mutex_t* mutex_;
};

#endif
