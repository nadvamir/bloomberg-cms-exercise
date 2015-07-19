#include "gmock/gmock.h"

#include <sstream>

#include "include/Message.h"

using namespace std;

TEST(AMessage, CanBeStreamedThroughAParentObject) {
    FilledMessage fm(10);
    Message& m = fm;
    stringstream ss;

    ss << m;

    ASSERT_THAT(ss.str(), testing::StrEq("10 HAS BEEN FILLED\n"));
}
