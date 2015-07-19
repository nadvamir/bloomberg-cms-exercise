#include "gmock/gmock.h"

#include <sstream>

#include "include/RevokedMessage.h"

using namespace std;

TEST(ARevokeMessage, AdheresToTheFormat) {
    RevokedMessage fm(10);
    Message& m = fm;
    stringstream ss;

    ss << m;

    ASSERT_THAT(ss.str(), testing::StrEq("10 HAS BEEN REVOKED\n"));
}
