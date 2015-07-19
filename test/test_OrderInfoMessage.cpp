#include "gmock/gmock.h"

#include <sstream>

#include "include/OrderInfoMessage.h"
#include "include/Order.h"

using namespace std;

TEST(AnOrderInfoMessage, AdheresToTheFormat) {
    CommodityPtr commodity(new Silver());
    OrderPtr order(new Order(
        Dealer("JPM"), Order::Sell, commodity, 10, 15.5));
    order->id(1);
    OrderInfoMessage fm(order);
    Message& m = fm;
    stringstream ss;
    string expected = "1 JPM SELL SILV 10 15.5";

    ss << m;

    ASSERT_THAT(ss.str(), testing::StrEq(expected));
}

TEST(AnOrderInfoMessage, IsNotKeepingReferencesToLiveOrders) {
    CommodityPtr commodity(new Silver());
    OrderPtr order(new Order(
        Dealer("JPM"), Order::Sell, commodity, 10, 15.5));
    order->id(1);
    OrderInfoMessage fm(order);
    Message& m = fm;
    stringstream ss;
    string expected = "1 JPM SELL SILV 10 15.5";

    order->id(1000);
    ss << m;

    ASSERT_THAT(ss.str(), testing::StrEq(expected));
}
