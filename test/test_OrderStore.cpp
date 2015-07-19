#include "gmock/gmock.h"

#include <functional>

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

    struct DealerPred : public unary_function<OrderPtr, bool> {
        Dealer dealer_;
        DealerPred(const Dealer& d) : dealer_(d) {}
        bool operator()(OrderPtr order) {
            return order->dealer() == dealer_;
        }
    };

    void SetUp() {
        order = OrderPtr(new Order(
            Dealer("JPM"), Order::Sell,
            CommodityPtr(new Gold),
            100, 59.99));

        order2 = OrderPtr(new Order(
            Dealer("BARX"), Order::Sell,
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

TEST_F(AnOrderStore, CanRemoveAnOrderById) {
    OrderStore store;
    long id = store.put(order);

    ASSERT_NO_THROW(store.remove(id));
    ASSERT_THROW(store.get(id), UnknownOrder);
}

TEST_F(AnOrderStore, ReturnsAllOrdersMatchingAPredicate) {
    OrderStore store;
    store.put(order); // JPM
    store.put(order2); // BARX

    vector<OrderPtr> jpOrders = store.filter(
        DealerPred(Dealer("JPM")));

    ASSERT_THAT(jpOrders.size(), Eq(1));
    ASSERT_THAT(jpOrders[0]->dealer(), Eq(Dealer("JPM")));
}
