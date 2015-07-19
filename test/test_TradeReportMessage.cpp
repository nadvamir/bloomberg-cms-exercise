#include "gmock/gmock.h"

#include <sstream>

#include "include/TradeReportMessage.h"
#include "include/Order.h"

using namespace std;

TEST(ATradeReportMessage, AdheresToTheFormat) {
    CommodityPtr commodity(new Silver());
    OrderPtr order(new Order(
        Dealer("JPM"), Order::Sell, commodity, 10, 15.5));
    TradeReportMessage fm(order);
    Message& m = fm;
    stringstream ss;
    string expected = "SOLD 10 SILV @ 15.5 FROM JPM";

    ss << m;

    ASSERT_THAT(ss.str(), testing::StrEq(expected));
}

