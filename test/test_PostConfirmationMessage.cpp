#include "gmock/gmock.h"

#include <sstream>

#include "include/PostConfirmationMessage.h"
#include "include/Order.h"

using namespace std;

TEST(APostConfirmationMessage, AdheresToTheFormat) {
    CommodityPtr commodity(new Silver());
    OrderPtr order(new Order(
        Dealer("JPM"), Order::Sell, commodity, 10, 15.5));
    order->id(1);
    PostConfirmationMessage fm(order);
    Message& m = fm;
    stringstream ss;
    string expected = "1 JPM SELL SILV 10 15.5\n"
                      " HAS BEEN POSTED\n";

    ss << m;

    ASSERT_THAT(ss.str(), testing::StrEq(expected));
}

