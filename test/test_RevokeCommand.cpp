#include "gmock/gmock.h"

#include "include/exceptions.h"
#include "include/RevokeCommand.h"
#include "test/MockOrderStore.h"

using namespace testing;
using namespace std;

class ARevokeCommand : public Test {
public:
    string ownId;
    long orderId;
    MockOrderStore* store;
    OrderPtr jpmOrder, barxOrder;

    void SetUp() {
        ownId = "JPM";
        orderId = 1;
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
    RevokeCommand cmd(ownId, orderId);
    EXPECT_CALL(*store, get(orderId))
        .WillOnce(ReturnRef(barxOrder));

    ASSERT_THROW(cmd(store), Unauthorized);
}
