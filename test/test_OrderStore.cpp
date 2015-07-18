#include "gmock/gmock.h"

#include <memory>
#include <map>

#include "include/Order.h"
#include "include/Commodity.h"
#include "include/Dealer.h"
#include "include/exceptions.h"

using namespace testing;
using namespace std;

class OrderStore {
    typedef map<long, OrderPtr> OrderMap;
    OrderMap store;
    
public:
    long put(OrderPtr& order) {
        long id = 0;
        order->id(id);
        store.insert(make_pair(id, order));
        return id;
    }

    OrderPtr& get(long id) {
        return store.find(id)->second;
    }
};

TEST(AnOrderStore, StoresOrdersAttachingIdsToThem) {
    OrderStore store;
    OrderPtr order = OrderPtr(new Order(
        Dealer("JPM"), Order::Sell,
        CommodityPtr(new Gold),
        100, 59.99));

    long id = store.put(order);

    ASSERT_THAT(store.get(id)->id(), Eq(id));
}
