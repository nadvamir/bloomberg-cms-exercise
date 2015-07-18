#include "gmock/gmock.h"

#include <memory>

#include "include/Commodity.h"
#include "include/Dealer.h"
#include "include/Order.h"
#include "include/exceptions.h"

using namespace testing;
using namespace std;

class AnOrder : public Test {
public:
    int quantity;
    double price;
    auto_ptr<Commodity> commodity;

    void SetUp() {
        quantity = 500;
        price = 1.0;
        commodity.reset(new Gold());
    }
};

TEST_F(AnOrder, CanBeBought) {
    Order order(Dealer("JPM"), Order::Buy, commodity, 1, price);

    ASSERT_THAT(order.side(), Eq(Order::Buy));
}

TEST_F(AnOrder, CanBeSold) {
    Order order(Dealer("JPM"), Order::Sell, commodity, 1, price);

    ASSERT_THAT(order.side(), Eq(Order::Sell));
}

TEST_F(AnOrder, HasRemainingQuantity) {
    Order order(Dealer("JPM"), Order::Sell, commodity, quantity, price);

    ASSERT_THAT(order.quantity(), Eq(quantity));
}

TEST_F(AnOrder, MustHaveAPositiveQuantity) {
    ASSERT_NO_THROW(Order(Dealer("JPM"), Order::Sell,
                          commodity, 1, price));

    commodity.reset(new Gold());

    ASSERT_THROW(Order(Dealer("JPM"), Order::Sell,
                       commodity, 0, price),
                 InvalidMessage);

    commodity.reset(new Gold());

    ASSERT_THROW(Order(Dealer("JPM"), Order::Sell,
                       commodity, -1, price),
                 InvalidMessage);
}

TEST_F(AnOrder, MustHaveAPositivePrice) {
    ASSERT_NO_THROW(Order(Dealer("JPM"), Order::Sell,
                          commodity, quantity, 1.0));

    commodity.reset(new Gold());

    ASSERT_THROW(Order(Dealer("JPM"), Order::Sell,
                       commodity, quantity, 0.0),
                 InvalidMessage);

    commodity.reset(new Gold());

    ASSERT_THROW(Order(Dealer("JPM"), Order::Sell,
                       commodity, quantity, -1.0),
                 InvalidMessage);
}

TEST_F(AnOrder, DoesNotHaveAnIdByDefault) {
    Order order(Dealer("JPM"), Order::Buy, commodity, quantity, price);

    ASSERT_THAT(order.id(), Eq(Order::NoID));
}

TEST_F(AnOrder, CanBeAssignedAnId) {
    Order order(Dealer("JPM"), Order::Buy, commodity, quantity, price);

    order.id(1);

    ASSERT_THAT(order.id(), Eq(1));
}

TEST_F(AnOrder, CanBeAggressed) {
    Order order(Dealer("JPM"), Order::Buy, commodity, quantity, price);

    order.aggress(50);

    ASSERT_THAT(order.quantity(), Eq(quantity - 50));
}

TEST_F(AnOrder, CannotBeAggressedMoreThanItsQuantity) {
    Order order(Dealer("JPM"), Order::Buy, commodity, quantity, price);

    ASSERT_THROW(order.aggress(quantity + 1), InvalidMessage);
}

TEST_F(AnOrder, IsNotFilledWhenCreated) {
    Order order(Dealer("JPM"), Order::Buy, commodity, quantity, price);

    ASSERT_THAT(order.isFilled(), Eq(false));
}
