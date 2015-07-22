#include "include/OrderStore.h"

#include "include/Order.h"
#include "include/SharedPtr.h"
#include "include/exceptions.h"
#include "include/CopyIf.h"

long OrderStore::put(OrderPtr& order) {
    long id = ++lastId;
    order->id(id);
    store.insert(std::make_pair(id, order));
    return id;
}

OrderPtr& OrderStore::get(long id) {
    OrderMap::iterator it = store.find(id);
    if (it == store.end()) {
        throw UnknownOrder();
    }
    return it->second;
}

