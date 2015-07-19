#include "gmock/gmock.h"

#include <sstream>

#include "include/FilledMessage.h"

using namespace std;

TEST(AFilledMessage, AdheresToTheFormat) {
    FilledMessage fm(10);
    Message& m = fm;
    stringstream ss;

    ss << m;

    ASSERT_THAT(ss.str(), testing::StrEq("10 HAS BEEN FILLED"));
}
