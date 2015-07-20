#include "gmock/gmock.h"

#include <string>
#include <sstream>

#include "include/exceptions.h"
#include "include/AggressCommand.h"
#include "test/MockOrderStore.h"

using namespace testing;
using namespace std;

class AnAggressCommand : public Test {
public:
    string ownId;
    long orderId;
    int initAmount, amount;
    double price;
    MockOrderStore* store;
    OrderPtr jpmOrder, barxOrder, filledOrder;

    void SetUp() {
        ownId = "JPM";
        orderId = 1;
        initAmount = 100;
        amount = 51;
        price = 59.99;
        store = new MockOrderStore(); // destroyed by shared ptr

        jpmOrder = OrderPtr(new Order(
            Dealer("JPM"), Order::Sell,
            CommodityPtr(new Gold),
            initAmount, price));
    }
};

TEST_F(AnAggressCommand, AggressedOnOrders) {
    AggressCommand cmd(orderId, amount);
    EXPECT_CALL(*store, get(orderId))
        .WillOnce(ReturnRef(jpmOrder));

    cmd(store);

    ASSERT_THAT(jpmOrder->quantity(), Eq(initAmount - amount));
}

//TEST_F(AnAggressCommand, ReturnsTradeReportMessage) {
//    AggressCommand cmd(orderId, amount);
//    EXPECT_CALL(*store, get(orderId))
//        .WillOnce(ReturnRef(jpmOrder));
//
//    stringstream ss, filled;
//    ss << *cmd(store);
//    filled << FilledMessage(orderId);
//
//    ASSERT_THAT(ss.str(), StrEq(filled.str()));
//}
//
//TEST_F(AnAggressCommand, ThrowsWhenRunOnNotOwnOrder) {
//    AggressCommand cmd(ownId, orderId);
//    EXPECT_CALL(*store, get(orderId))
//        .WillOnce(ReturnRef(barxOrder));
//
//    ASSERT_THROW(cmd(store), Unauthorized);
//}
//
