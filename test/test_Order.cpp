#include "gmock/gmock.h"

#include "include/Commodity.h"

using namespace std;

class Order {
public:
    enum Side { Buy, Sell };

private:
    Side side_;

public:
    Order(Side s) : side_(s) {}

    Side side() const { return side_; }
};

TEST(AnOrder, CanBeBought) {
    Order order(Order::Buy);

    ASSERT_TRUE(order.side() == Order::Buy);
}

TEST(AnOrder, CanBeSold) {
    Order order(Order::Sell);

    ASSERT_TRUE(order.side() == Order::Sell);
}

