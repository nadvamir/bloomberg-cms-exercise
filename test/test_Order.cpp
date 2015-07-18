#include "gmock/gmock.h"

#include "include/Commodity.h"
#include "include/Dealer.h"
#include "include/Order.h"
#include "include/exceptions.h"
#include "include/SharedPtr.h"

using namespace testing;
using namespace std;

class AnOrder : public Test {
public:
    int quantity;
    double price;
    SharedPtr<Commodity> commodity;
    SharedPtr<Order> orderPtr;

    void SetUp() {
        quantity = 500;
        price = 1.0;
        commodity = SharedPtr<Commodity>(new Gold());
        orderPtr = SharedPtr<Order>(new Order(
            Dealer("JPM"), Order::Buy, commodity, quantity, price));
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
    ASSERT_THAT(orderPtr->quantity(), Eq(quantity));
}

TEST_F(AnOrder, MustHaveAPositiveQuantity) {
    ASSERT_NO_THROW(Order(Dealer("JPM"), Order::Sell,
                          commodity, 1, price));

    ASSERT_THROW(Order(Dealer("JPM"), Order::Sell,
                       commodity, 0, price),
                 InvalidMessage);

    ASSERT_THROW(Order(Dealer("JPM"), Order::Sell,
                       commodity, -1, price),
                 InvalidMessage);
}

TEST_F(AnOrder, MustHaveAPositivePrice) {
    ASSERT_NO_THROW(Order(Dealer("JPM"), Order::Sell,
                          commodity, quantity, 1.0));

    ASSERT_THROW(Order(Dealer("JPM"), Order::Sell,
                       commodity, quantity, 0.0),
                 InvalidMessage);

    ASSERT_THROW(Order(Dealer("JPM"), Order::Sell,
                       commodity, quantity, -1.0),
                 InvalidMessage);
}

TEST_F(AnOrder, DoesNotHaveAnIdByDefault) {
    ASSERT_THAT(orderPtr->id(), Eq(Order::NoID));
}

TEST_F(AnOrder, CanBeAssignedAnId) {
    orderPtr->id(1);

    ASSERT_THAT(orderPtr->id(), Eq(1));
}

TEST_F(AnOrder, CanBeAggressed) {
    orderPtr->aggress(50);

    ASSERT_THAT(orderPtr->quantity(), Eq(quantity - 50));
}

TEST_F(AnOrder, CannotBeAggressedMoreThanItsQuantity) {
    ASSERT_THROW(orderPtr->aggress(quantity + 1), InvalidMessage);
}

TEST_F(AnOrder, IsNotFilledWhenCreated) {
    ASSERT_THAT(orderPtr->isFilled(), Eq(false));
}

TEST_F(AnOrder, IsFilledWhenAggressedInFull) {
    orderPtr->aggress(quantity);

    ASSERT_THAT(orderPtr->isFilled(), Eq(true));
}
