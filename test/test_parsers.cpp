#include "gmock/gmock.h"

#include <string>
#include <sstream>

#include "include/Command.h"
#include "include/RevokeCommand.h"
#include "include/parsers.h"

using namespace testing;
using namespace std;

TEST(ParseMessage, UnderstandsRevokeCommand) {
    stringstream ss("JPM REVOKE 1");
    CommandPtr cmd = parseMessage(ss);

    ASSERT_TRUE(dynamic_cast<RevokeCommand*>(REPR(cmd)));
}
