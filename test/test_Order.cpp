#include "gmock/gmock.h"

#include "include/Commodity.h"
#include "include/Order.h"
#include "include/exceptions.h"

using namespace testing;
using namespace std;

TEST(AnOrder, CanBeBought) {
    Order order(Order::Buy, 1);

    ASSERT_THAT(order.side(), Eq(Order::Buy));
}

TEST(AnOrder, CanBeSold) {
    Order order(Order::Sell, 1);

    ASSERT_THAT(order.side(), Eq(Order::Sell));
}

TEST(AnOrder, HasRemainingQuantity) {
    int quantity = 500;
    Order order(Order::Sell, quantity);

    ASSERT_THAT(order.quantity(), Eq(quantity));
}

TEST(AnOrder, MustHaveAPositiveQuantity) {
    ASSERT_NO_THROW(Order(Order::Sell, 1));
    ASSERT_THROW(Order(Order::Sell, 0), InvalidMessage);
    ASSERT_THROW(Order(Order::Sell, -1), InvalidMessage);
}
