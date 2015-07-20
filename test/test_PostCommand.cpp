#include "gmock/gmock.h"

#include <string>
#include <sstream>

#include "include/exceptions.h"
#include "include/PostCommand.h"
#include "test/MockOrderStore.h"

using namespace testing;
using namespace std;

class APostCommand : public Test {
public:
    string ownId;
    long orderId;
    int initAmount, amount;
    double price;
    MockOrderStore* store;
    OrderPtr jpmOrder, barxOrder, filledOrder;
    CommodityPtr commodity;

    void SetUp() {
        ownId = "JPM";
        orderId = 1;
        initAmount = 100;
        amount = 51;
        price = 59.99;
        commodity = CommodityPtr(new Gold);
        store = new MockOrderStore(); // destroyed by shared ptr

        jpmOrder = OrderPtr(new Order(
            Dealer("JPM"), Order::Buy,
            commodity, initAmount, price));
    }
};

TEST_F(APostCommand, SubmitsAnOrder) {
    OrderPtr submittedOrder;
    PostCommand cmd(Dealer("JPM"), Order::Buy, commodity,
                    amount, price);
    EXPECT_CALL(*store, put(_))
        .WillOnce(SaveArg<0>(&submittedOrder));

    cmd(store);

    ASSERT_THAT(submittedOrder->dealer(), Eq(Dealer("JPM")));
    ASSERT_THAT(submittedOrder->side(), Eq(Order::Buy));
    ASSERT_TRUE(*(submittedOrder->commodity()) == *commodity);
    ASSERT_THAT(submittedOrder->quantity(), Eq(amount));
    ASSERT_THAT(submittedOrder->price(), Eq(price));
}

TEST_F(APostCommand, ReturnsPostConfirmationMessage) {
    OrderPtr submittedOrder;
    PostCommand cmd(Dealer("JPM"), Order::Buy, commodity,
                    amount, price);
    EXPECT_CALL(*store, put(_))
        .WillOnce(SaveArg<0>(&submittedOrder));

    stringstream ss, pconf;
    ss << *cmd(store);
    pconf << PostConfirmationMessage(submittedOrder);

    ASSERT_THAT(ss.str(), StrEq(pconf.str()));

}

