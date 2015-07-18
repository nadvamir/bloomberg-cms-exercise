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
    typedef map<long, Order> OrderMap;
    OrderMap store;
    
public:
//     long put(Order& order) {
//         store.insert(make_pair(0, order));
//         return 0;
//     }
// 
//     Order& get(long id) {
//         return store.find(id)->second;
//     }
};

// TEST(AnOrderStore, StoresOrders) {
//     OrderStore store;
//     Order order(Dealer("JPM"), Order::Sell,
//                 std::auto_ptr<Commodity> (new Gold),
//                 100, 59.99);
// 
//     long id = store.put(order);
// 
//     ASSERT_THAT(store.get(id), Eq(order));
// }
