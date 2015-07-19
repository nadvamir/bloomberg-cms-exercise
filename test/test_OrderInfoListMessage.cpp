#include "gmock/gmock.h"

#include <sstream>
#include <vector>

#include "include/OrderInfoListMessage.h"
#include "include/Order.h"

using namespace std;

TEST(AnOrderInfoListMessage, AdheresToTheFormat) {
    CommodityPtr commodity(new Silver());
    OrderPtr order(new Order(
        Dealer("JPM"), Order::Sell, commodity, 10, 15.5));
    order->id(1);
    OrderPtr order2(new Order(
        Dealer("BARX"), Order::Buy, commodity, 10, 15.5));
    order2->id(2);

    vector<OrderPtr> orders;
    orders.push_back(order);
    orders.push_back(order2);

    OrderInfoListMessage fm(orders);
    Message& m = fm;
    stringstream ss;
    string expected = "1 JPM SELL SILV 10 15.5\n"
                      "2 BARX BUY SILV 10 15.5\n"
                      "END OF LIST";

    ss << m;

    ASSERT_THAT(ss.str(), testing::StrEq(expected));
}

