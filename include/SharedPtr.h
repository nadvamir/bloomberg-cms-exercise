#ifndef SHARED_PTR_H
#define SHARED_PTR_H

template <class T>
class SharedPtr {
    typedef T* StoredType;
    typedef T& ReferenceType;

    StoredType ptr_;
    int* refCount_;
public:
    explicit SharedPtr(StoredType ptr)
    : ptr_(ptr), refCount_(new int(1)) {}

    SharedPtr(const SharedPtr& sptr)
    : ptr_(sptr.ptr_), refCount_(sptr.refCount_) {
        ++(*refCount_);
    }

    SharedPtr& operator=(const SharedPtr& sptr) {
        --(*refCount_);
        if (0 == *refCount_) {
            delete ptr_;
            delete refCount_;
        }

        ptr_ = sptr.ptr_;
        refCount_ = sptr.refCount_;
        ++(*refCount_);

        return *this;
    }

    ~SharedPtr() {
        --(*refCount_);
        if (0 == *refCount_) {
            delete ptr_;
            delete refCount_;
        }
    }

    ReferenceType operator*() { return *ptr_; }

    StoredType operator->() { return ptr_; }
};

#endif
