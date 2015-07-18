#include "gmock/gmock.h"

#include "include/SharedPtr.h"

using namespace testing;
using namespace std;

TEST(ASharedPtr, ProvidesDereferenceOperator) {
    int* realPtr = new int;
    *realPtr = 42;
    SharedPtr<int> pointer(realPtr);

    ASSERT_THAT(*pointer, Eq(42));
}

struct TestStruct {
    int a;
};
TEST(ASharedPtr, ProvidesArrowOperator) {
    TestStruct* p = new TestStruct;
    p->a = 42;
    SharedPtr<TestStruct> pointer(p);

    ASSERT_THAT(pointer->a, Eq(42));
}
