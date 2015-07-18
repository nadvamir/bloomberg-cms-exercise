#include "gmock/gmock.h"

#include "include/OrderStore.h"
#include "include/Order.h"
#include "include/Commodity.h"
#include "include/Dealer.h"
#include "include/exceptions.h"

using namespace testing;
using namespace std;

TEST(AnOrderStore, StoresOrdersAttachingIdsToThem) {
    OrderStore store;
    OrderPtr order = OrderPtr(new Order(
        Dealer("JPM"), Order::Sell,
        CommodityPtr(new Gold),
        100, 59.99));

    long id = store.put(order);

    ASSERT_THAT(store.get(id)->id(), Eq(id));
}
