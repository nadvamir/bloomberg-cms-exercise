#include "gmock/gmock.h"

#include <string>
#include <sstream>

#include "include/exceptions.h"
#include "include/ListCommand.h"
#include "include/OrderStore.h"

using namespace testing;
using namespace std;

class Slow_AListCommand : public Test {
public:
    string ownId;
    long orderId;
    OrderStorePtr store;
    OrderPtr jpmOrder, barxOrder, silvOrder;
    string jpmStr, barxStr, silvStr;

    void SetUp() {
        ownId = "JPM";
        orderId = 1;
        store = new OrderStore(); // because of templated filter
                                  // function, we can't use gmock

        jpmOrder = OrderPtr(new Order(
            Dealer("JPM"), Order::Sell,
            CommodityPtr(new Gold),
            100, 59.99));

        silvOrder = OrderPtr(new Order(
            Dealer("JPM"), Order::Sell,
            CommodityPtr(new Silver),
            100, 59.99));


        barxOrder = OrderPtr(new Order(
            Dealer("BARX"), Order::Sell,
            CommodityPtr(new Gold),
            100, 59.99));

        store->put(jpmOrder);
        store->put(silvOrder);
        store->put(barxOrder);

        stringstream ss;
        ss << *jpmOrder; jpmStr = ss.str(); ss.str(string());
        ss << *silvOrder; silvStr = ss.str(); ss.str(string());
        ss << *barxOrder; barxStr = ss.str();
    }
};

TEST_F(Slow_AListCommand, CommodityPredicateMatchesCommodities) {
    CommodityPred pred(CommodityPtr(new Gold));

    ASSERT_THAT(pred(jpmOrder), Eq(true));
    ASSERT_THAT(pred(silvOrder), Eq(false));
}

TEST_F(Slow_AListCommand, CommodityAndDealerPredicateWorks) {
    CommodityAndDealerPred pred(CommodityPtr(new Gold), Dealer("JPM"));

    ASSERT_THAT(pred(jpmOrder), Eq(true));
    ASSERT_THAT(pred(silvOrder), Eq(false));
    ASSERT_THAT(pred(barxOrder), Eq(false));
}

TEST_F(Slow_AListCommand, ReturnsAllOrdersByDefault) {
    ListCommand cmd;

    stringstream ss, expected;
    expected << jpmStr << "\n" << silvStr << "\n"
             << barxStr << "\nEND OF LIST";

    ss << *cmd(store);

    ASSERT_THAT(ss.str(), StrEq(expected.str()));
}
