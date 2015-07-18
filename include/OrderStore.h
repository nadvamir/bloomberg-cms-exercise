#ifndef ORDER_STORE_H
#define ORDER_STORE_H

#include <map>

#include "include/Order.h"
#include "include/exceptions.h"

class OrderStore {
    typedef std::map<long, OrderPtr> OrderMap;
    OrderMap store;
    
public:
    long put(OrderPtr& order) {
        long id = 0;
        order->id(id);
        store.insert(std::make_pair(id, order));
        return id;
    }

    OrderPtr& get(long id) {
        return store.find(id)->second;
    }
};

#endif
