#include "gmock/gmock.h"

#include "include/SharedPtr.h"

using namespace testing;
using namespace std;

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

