#include "gmock/gmock.h"

#include <string>
#include <sstream>

#include "include/RevokeCommand.h"
#include "include/CheckCommand.h"
#include "include/AggressCommand.h"
#include "include/PostCommand.h"
#include "include/ListCommand.h"
#include "include/parsers.h"
#include "include/exceptions.h"

using namespace testing;
using namespace std;

TEST(ParseMessage, UnderstandsRevokeCommand) {
    stringstream ss("JPM REVOKE 1");
    CommandPtr cmd = parseMessage(ss);

    ASSERT_TRUE(dynamic_cast<RevokeCommand*>(REPR(cmd)));
}

TEST(ParseMessage, UnderstandsCheckCommand) {
    stringstream ss("JPM CHECK 1");
    CommandPtr cmd = parseMessage(ss);

    ASSERT_TRUE(dynamic_cast<CheckCommand*>(REPR(cmd)));
}

TEST(ParseMessage, ThrowsInvalidMessageIfCmdNotFound) {
    stringstream ss("JPM STEAL 1");

    ASSERT_THROW(parseMessage(ss), InvalidMessage);
}

TEST(ParseMessage, ThrowsUnknownDealerIfDealerNotFound) {
    stringstream ss("MAXBANK CHECK 1");

    ASSERT_THROW(parseMessage(ss), UnknownDealer);
}

TEST(ParseMessage, ParsesRevokeCommandCorrectly) {
    RevokeCommand expected(Dealer("JPM"), 2);
    stringstream ss("JPM REVOKE 2");
    CommandPtr cmd = parseMessage(ss);

    RevokeCommand *pCmd = dynamic_cast<RevokeCommand*>(REPR(cmd));
    ASSERT_THAT(*pCmd, Eq(expected));
}

TEST(ParseMessage, ParsesCheckCommandCorrectly) {
    CheckCommand expected(Dealer("BARX"), 2);
    stringstream ss("BARX CHECK 2");
    CommandPtr cmd = parseMessage(ss);

    CheckCommand *pCmd = dynamic_cast<CheckCommand*>(REPR(cmd));
    ASSERT_THAT(*pCmd, Eq(expected));
}

TEST(ParseMessage, ParsesAggressCommandCorrectly) {
    AggressCommand expected(1, 10);
    stringstream ss("BARX AGGRESS 1 10");
    CommandPtr cmd = parseMessage(ss);

    AggressCommand *pCmd = dynamic_cast<AggressCommand*>(REPR(cmd));
    ASSERT_THAT(*pCmd, Eq(expected));
}

TEST(ParseMessage, ParsesPostCommandCorrectly) {
    PostCommand expected(Dealer("DB"), Order::Sell, 
                         CommodityPtr(new Rice), 1, 10.5);
    stringstream ss("DB POST SELL RICE 1 10.5");
    CommandPtr cmd = parseMessage(ss);

    PostCommand *pCmd = dynamic_cast<PostCommand*>(REPR(cmd));
    ASSERT_THAT(*pCmd, Eq(expected));
}

TEST(ParseMessage, ParsesDefaultListCommandCorrectly) {
    ListCommand expected = ListCommand(CommodityPtr(), Dealer());
    stringstream ss("DB LIST");
    CommandPtr cmd = parseMessage(ss);

    ListCommand *pCmd = dynamic_cast<ListCommand*>(REPR(cmd));
    ASSERT_THAT(*pCmd, Eq(expected));
}

TEST(ParseMessage, ParsesCommodityListCommandCorrectly) {
    ListCommand expected = ListCommand(CommodityPtr(new Oil), Dealer());
    stringstream ss("DB LIST OIL");
    CommandPtr cmd = parseMessage(ss);

    ListCommand *pCmd = dynamic_cast<ListCommand*>(REPR(cmd));
    ASSERT_THAT(*pCmd, Eq(expected));
}

