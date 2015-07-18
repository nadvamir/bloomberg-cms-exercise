#include "gmock/gmock.h"

using namespace testing;
using namespace std;

template <class T>
class SharedPtr {
    typedef T* StoredType;
    typedef T& ReferenceType;

    StoredType ptr_;
public:
    SharedPtr(StoredType ptr) : ptr_(ptr) {
    }
    ReferenceType operator*() { return *ptr_; }
};

TEST(ASharedPtr, ProvidesDereferenceOperator) {
    int* realPtr = new int;
    *realPtr = 42;
    SharedPtr<int> pointer(realPtr);

    ASSERT_THAT(*pointer, Eq(42));
}
