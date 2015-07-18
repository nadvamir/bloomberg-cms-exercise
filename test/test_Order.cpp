#include "gmock/gmock.h"

#include "include/Commodity.h"

using namespace std;

class Order {
public:
    enum Side { Buy, Sell };

private:
    Side side_;

    Order(Side s) : side_(s) {}

public:
    static Order buy() {
        return Order(Buy);
    }

    static Order sell() {
        return Order(Sell);
    }

    Side side() const { return side_; }
};

TEST(AnOrder, CanBeBought) {
    Order order = Order::buy();

    ASSERT_TRUE(order.side() == Order::Buy);
}

TEST(AnOrder, CanBeSold) {
    Order order = Order::sell();

    ASSERT_TRUE(order.side() == Order::Sell);
}

