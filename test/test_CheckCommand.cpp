#include "gmock/gmock.h"

#include <string>
#include <sstream>

#include "include/exceptions.h"
#include "include/CheckCommand.h"
#include "test/MockOrderStore.h"

using namespace testing;
using namespace std;

class ACheckCommand : public Test {
public:
    string ownId;
    long orderId;
    MockOrderStore* store;
    OrderPtr jpmOrder, barxOrder, filledOrder;

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

        filledOrder = OrderPtr(new Order(
            Dealer("JPM"), Order::Sell,
            CommodityPtr(new Gold),
            1, 59.99));
        filledOrder->aggress(1);
    }
};

TEST_F(ACheckCommand, ThrowsWhenRunOnNotOwnOrder) {
    CheckCommand cmd(ownId, orderId);
    EXPECT_CALL(*store, get(orderId))
        .WillOnce(ReturnRef(barxOrder));

    ASSERT_THROW(cmd(store), Unauthorized);
}

TEST_F(ACheckCommand, ReturnsFilledMessageWhenOrderIsFilled) {
    CheckCommand cmd(ownId, orderId);
    EXPECT_CALL(*store, get(orderId))
        .WillOnce(ReturnRef(filledOrder));

    stringstream ss, filled;
    ss << *cmd(store);
    filled << FilledMessage(orderId);

    ASSERT_THAT(ss.str(), StrEq(filled.str()));
}

TEST_F(ACheckCommand, ReturnsOrderInfoMessageWhenOrderIsNotFilled) {
    CheckCommand cmd(ownId, orderId);
    EXPECT_CALL(*store, get(orderId))
        .WillOnce(ReturnRef(jpmOrder));

    stringstream ss, oinfo;
    ss << *cmd(store);
    oinfo << OrderInfoMessage(jpmOrder);

    ASSERT_THAT(ss.str(), StrEq(oinfo.str()));
}
