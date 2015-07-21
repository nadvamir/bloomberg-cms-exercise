#include "gmock/gmock.h"

#include "include/SharedPtr.h"

using namespace testing;
using namespace std;

namespace {
struct TestStruct {
    int a;
    static int constructionCount;
    static int destructionCount;

    static void reset() {
        TestStruct::constructionCount = 0;
        TestStruct::destructionCount = 0;
    }

    TestStruct(int val) : a(val) {
        ++TestStruct::constructionCount;
    }
    TestStruct(const TestStruct& ts) {
        ++TestStruct::constructionCount;
        a = ts.a;
    }
    ~TestStruct() { ++TestStruct::destructionCount; }
};

struct Base {
    virtual ~Base() {}
    virtual int f() { return 1; }
};
struct Derived : Base {
    virtual int f() { return 2; }
};

struct Data {
    int a, b;
};
}

int TestStruct::constructionCount = 0;
int TestStruct::destructionCount = 0;

class ASharedPtr : public Test {
public:
    void SetUp() {
        TestStruct::reset();
    }
};

TEST_F(ASharedPtr, IsNullByDefault) {
    ASSERT_NO_THROW({ SharedPtr<int> ptr; });
}

TEST_F(ASharedPtr, ProvidesDereferenceOperator) {
    int* realPtr = new int;
    *realPtr = 42;
    SharedPtr<int> pointer(realPtr);

    ASSERT_THAT(*pointer, Eq(42));
}

TEST_F(ASharedPtr, ProvidesArrowOperator) {
    SharedPtr<TestStruct> pointer(new TestStruct(42));

    ASSERT_THAT(pointer->a, Eq(42));
}

TEST_F(ASharedPtr, DoesNotCopyTheUnderlyingObject) {
    SharedPtr<TestStruct> pointer(new TestStruct(42));
    SharedPtr<TestStruct> clone(pointer);

    ASSERT_THAT(TestStruct::constructionCount, Eq(1));
}

TEST_F(ASharedPtr, OnlyDestroysTheObjectOnce) {
    {
        SharedPtr<TestStruct> pointer(new TestStruct(42));
        {
            SharedPtr<TestStruct> clone(pointer);
        }
    }

    ASSERT_THAT(TestStruct::destructionCount, Eq(1));
}

TEST_F(ASharedPtr, DestroysAPointeeIfAssignedNewOneAndWasLast) {
    SharedPtr<TestStruct> pointer(new TestStruct(42));
    pointer = SharedPtr<TestStruct>(new TestStruct(43));

    ASSERT_THAT(TestStruct::destructionCount, Eq(1));
}

TEST_F(ASharedPtr, LeavesAPointeeIfAssignedNewOneAndWasNotLast) {
    SharedPtr<TestStruct> pointer(new TestStruct(42));
    SharedPtr<TestStruct> pointer2 = pointer;
    pointer = SharedPtr<TestStruct>(new TestStruct(43));

    ASSERT_THAT(TestStruct::destructionCount, Eq(0));
}

TEST_F(ASharedPtr, CanBeAssignedEvenIfItWasNull) {
    ASSERT_NO_THROW({
        SharedPtr<TestStruct> ptr;
        ptr = SharedPtr<TestStruct>(new TestStruct(42));
    });
}

TEST_F(ASharedPtr, SupportsANULLCheck) {
    SharedPtr<TestStruct> pointer;
    TestStruct* p = new TestStruct(42);

    ASSERT_THAT(pointer.isNull(), Eq(true));

    pointer = SharedPtr<TestStruct>(p);
    ASSERT_THAT(pointer.isNull(), Eq(false));
}

TEST_F(ASharedPtr, SupportsPolymorphism) {
    SharedPtr<Base> base(new Derived());

    ASSERT_THAT(base->f(), Eq(Derived().f()));
}

TEST_F(ASharedPtr, CanBeThreadSafeWithRecursiveMutex) {
    SharedPtr<Data, true> ptr(new Data());
    ptr->a = 5;
    ptr->b = 10;
    ASSERT_TRUE(ptr->a < ptr->b);
    // a proper test would require me to mix in
    // another template parameter to suply my own
    // locking class
}
