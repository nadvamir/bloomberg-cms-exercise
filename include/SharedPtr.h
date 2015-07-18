#ifndef SHARED_PTR_H
#define SHARED_PTR_H

template <class T>
class SharedPtr {
    typedef T* StoredType;
    typedef T& ReferenceType;

    StoredType ptr_;
public:
    SharedPtr(StoredType ptr) : ptr_(ptr) {
    }

    ReferenceType operator*() { return *ptr_; }

    StoredType operator->() { return ptr_; }
};

#endif
