#ifndef SHARED_PTR_H
#define SHARED_PTR_H

// This is the most basic implementation of a shared pointer
// Not thead safe at this point in time
template <class T>
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

    SharedPtr(const SharedPtr& sptr)
    : ptr_(sptr.ptr_), refCount_(sptr.refCount_) {
        if (NULL != refCount_) {
            ++(*refCount_);
        }
    }

    SharedPtr& operator=(const SharedPtr& sptr) {
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

    ReferenceType operator*() { return *ptr_; }
    const ReferenceType operator*() const { return *ptr_; }

    StoredType operator->() { return ptr_; }
    StoredType operator->() const { return ptr_; }

    bool isNull() const { return ptr_ == NULL; }

    friend StoredType REPR(const SharedPtr& p) {
        return p.ptr_;
    }
};

#endif
