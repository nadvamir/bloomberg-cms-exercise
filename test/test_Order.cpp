#include "gmock/gmock.h"

#include "include/Commodity.h"
#include "include/Order.h"
#include "include/exceptions.h"

using namespace testing;
using namespace std;

class AnOrder : public Test {
public:
    int quantity;
    float price;

    void SetUp() {
        quantity = 500;
        price = 1.0;
    }
};

TEST_F(AnOrder, CanBeBought) {
    Order order(Order::Buy, 1, price);

    ASSERT_THAT(order.side(), Eq(Order::Buy));
}

TEST_F(AnOrder, CanBeSold) {
    Order order(Order::Sell, 1, price);

    ASSERT_THAT(order.side(), Eq(Order::Sell));
}

TEST_F(AnOrder, HasRemainingQuantity) {
    Order order(Order::Sell, quantity, price);

    ASSERT_THAT(order.quantity(), Eq(quantity));
}

TEST_F(AnOrder, MustHaveAPositiveQuantity) {
    ASSERT_NO_THROW(Order(Order::Sell, 1, price));
    ASSERT_THROW(Order(Order::Sell, 0, price), InvalidMessage);
    ASSERT_THROW(Order(Order::Sell, -1, price), InvalidMessage);
}

TEST_F(AnOrder, MustHaveAPositivePrice) {
    ASSERT_NO_THROW(Order(Order::Sell, quantity, 1.0));
    ASSERT_THROW(Order(Order::Sell, quantity, 0.0), InvalidMessage);
    ASSERT_THROW(Order(Order::Sell, quantity, -1.0), InvalidMessage);
}
