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
    Dealer dealer;
    auto_ptr<Commodity> commodity;

    void SetUp() {
        quantity = 500;
        price = 1.0;
        dealer = Dealer("JPM");
        commodity.reset(new Gold());
    }
};

TEST_F(AnOrder, CanBeBought) {
    Order order(dealer, Order::Buy, commodity, 1, price);

    ASSERT_THAT(order.side(), Eq(Order::Buy));
}

TEST_F(AnOrder, CanBeSold) {
    Order order(dealer, Order::Sell, commodity, 1, price);

    ASSERT_THAT(order.side(), Eq(Order::Sell));
}

TEST_F(AnOrder, HasRemainingQuantity) {
    Order order(dealer, Order::Sell, commodity, quantity, price);

    ASSERT_THAT(order.quantity(), Eq(quantity));
}

TEST_F(AnOrder, MustHaveAPositiveQuantity) {
    ASSERT_NO_THROW(Order(dealer, Order::Sell,
                          commodity, 1, price));

    commodity.reset(new Gold());

    ASSERT_THROW(Order(dealer, Order::Sell,
                       commodity, 0, price),
                 InvalidMessage);

    commodity.reset(new Gold());

    ASSERT_THROW(Order(dealer, Order::Sell,
                       commodity, -1, price),
                 InvalidMessage);
}

TEST_F(AnOrder, MustHaveAPositivePrice) {
    ASSERT_NO_THROW(Order(dealer, Order::Sell,
                          commodity, quantity, 1.0));

    commodity.reset(new Gold());

    ASSERT_THROW(Order(dealer, Order::Sell,
                       commodity, quantity, 0.0),
                 InvalidMessage);

    commodity.reset(new Gold());

    ASSERT_THROW(Order(dealer, Order::Sell,
                       commodity, quantity, -1.0),
                 InvalidMessage);
}

TEST_F(AnOrder, DoesNotHaveAnIdByDefault) {
    Order order(dealer, Order::Buy, commodity, quantity, price);

    ASSERT_THAT(order.id(), Eq(Order::NoID));
}
