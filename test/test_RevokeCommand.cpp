#include "gmock/gmock.h"

#include <string>

#include "include/Command.h"
#include "include/RevokedMessage.h"
#include "include/Dealer.h"
#include "include/exceptions.h"
#include "test/MockOrderStore.h"

using namespace testing;
using namespace std;

class RevokeCommand : public Command {
    Dealer dealer_;
    long orderId_;
public:
    RevokeCommand(const Dealer& dealer, long orderId)
    : dealer_(dealer), orderId_(orderId) {}

    MessagePtr operator()(OrderStorePtr store) {
        OrderPtr order = store->get(orderId_);
        if (order->dealer() != dealer_) {
            throw Unauthorized();
        }

        return MessagePtr();
    }
};

class ARevokeCommand : public Test {
public:
    string ownId;
    MockOrderStore* store;
    OrderPtr jpmOrder, barxOrder;

    void SetUp() {
        ownId = "JPM";
        store = new MockOrderStore(); // destroyed by shared ptr

        jpmOrder = OrderPtr(new Order(
            Dealer("JPM"), Order::Sell,
            CommodityPtr(new Gold),
            100, 59.99));

        barxOrder = OrderPtr(new Order(
            Dealer("BARX"), Order::Sell,
            CommodityPtr(new Gold),
            100, 59.99));
    }
};

TEST_F(ARevokeCommand, ThrowsWhenRunOnNotOwnOrder) {
    long orderId = 1;
    RevokeCommand cmd(ownId, orderId);
    EXPECT_CALL(*store, get(orderId))
        .WillOnce(ReturnRef(barxOrder));

    ASSERT_THROW(cmd(store), Unauthorized);
}
