#include "gmock/gmock.h"

#include "include/OrderStore.h"
#include "include/Order.h"
#include "include/Commodity.h"
#include "include/Dealer.h"
#include "include/exceptions.h"

using namespace testing;
using namespace std;

class AnOrderStore : public Test {
public:
    OrderPtr order, order2;
    void SetUp() {
        order = OrderPtr(new Order(
            Dealer("JPM"), Order::Sell,
            CommodityPtr(new Gold),
            100, 59.99));

        order2 = OrderPtr(new Order(
            Dealer("JPM"), Order::Sell,
            CommodityPtr(new Gold),
            100, 59.99));
    }
};

TEST_F(AnOrderStore, StoresOrdersAttachingIdsToThem) {
    OrderStore store;

    long id = store.put(order);

    ASSERT_THAT(store.get(id)->id(), Eq(id));
}

TEST_F(AnOrderStore, StoresUniqueIdsToEveryOrder) {
    OrderStore store;

    long id = store.put(order);
    long id2 = store.put(order2);

    ASSERT_THAT(id, Ne(id2));
}

TEST_F(AnOrderStore, ThrowsAnExceptionIfOrderIsNotFound) {
    OrderStore store;

    long id = store.put(order);

    ASSERT_THROW(store.get(id + 1), UnknownOrder);
}

