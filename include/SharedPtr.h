#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <pthread.h>
#include <unistd.h>

const bool THREAD_SAFE = true; // for clarity

// not thread-safe implementation:
template <class T, bool ThreadSafe = !THREAD_SAFE>
class SharedPtr {
    typedef T* StoredType;
    typedef T& ReferenceType;

    StoredType ptr_;
    int* refCount_;
public:
    SharedPtr() : ptr_(NULL), refCount_(NULL) {}

    // Can't make it explicit to use it in tests...
    SharedPtr(StoredType ptr)
    : ptr_(ptr), refCount_(new int(1)) {}

    SharedPtr(const SharedPtr<T>& sptr)
    : ptr_(sptr.ptr_), refCount_(sptr.refCount_) {
        if (NULL != refCount_) {
            ++(*refCount_);
        }
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& sptr) {
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

    ~SharedPtr() {
        if (NULL != refCount_ && 0 == --(*refCount_)) {
            delete ptr_;
            delete refCount_;
        }
    }

    ReferenceType operator*() const { return *ptr_; }

    StoredType operator->() const {
        return ptr_;
    }

    bool isNull() const { return ptr_ == NULL; }

    friend StoredType REPR(const SharedPtr<T>& p) {
        return p.ptr_;
    }
};

// thread-safe specialisation
template <class T>
class SharedPtr<T, THREAD_SAFE> {
    typedef T* StoredType;
    typedef T& ReferenceType;

    StoredType ptr_;
    int* refCount_;

    pthread_mutex_t* mutex_;

    // a proxy lock used as a temporary object
    // for operator->
    template<class T_>
    class LockingProxy {
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

    typedef LockingProxy<T> PointedType;

public:
    SharedPtr() : ptr_(NULL), refCount_(NULL), mutex_(NULL) {}

    SharedPtr(StoredType ptr)
    : ptr_(ptr), refCount_(new int(1))
    , mutex_(new pthread_mutex_t) {
        pthread_mutexattr_t attr;

        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(mutex_, &attr);
    }

    SharedPtr(const SharedPtr<T, THREAD_SAFE>& sptr)
    : ptr_(sptr.ptr_), refCount_(sptr.refCount_)
    , mutex_(sptr.mutex_) {
        if (NULL != refCount_) {
            pthread_mutex_lock(mutex_);
            ++(*refCount_);
            pthread_mutex_unlock(mutex_);
        }
    }

    SharedPtr<T, THREAD_SAFE>& operator=(
            const SharedPtr<T, THREAD_SAFE>& sptr) {
        if (NULL != refCount_) {
            pthread_mutex_lock(mutex_);
            --(*refCount_);
            pthread_mutex_unlock(mutex_);

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
            pthread_mutex_lock(mutex_);
            ++(*refCount_);
            pthread_mutex_unlock(mutex_);
        }

        return *this;
    }

    ~SharedPtr() {
        if (NULL != refCount_) {
            pthread_mutex_lock(mutex_);
            --(*refCount_);
            pthread_mutex_unlock(mutex_);

            if (0 == *refCount_) {
                delete ptr_;
                delete refCount_;
                pthread_mutex_destroy(mutex_);
                delete mutex_;
            }
        }
    }

    ReferenceType operator*() const { return *ptr_; }

    PointedType operator->() const {
        return LockingProxy<T>(ptr_, mutex_);
    }

    bool isNull() const { return ptr_ == NULL; }

    friend StoredType REPR(const SharedPtr<T, THREAD_SAFE>& p) {
        return p.ptr_;
    }

};

#endif
