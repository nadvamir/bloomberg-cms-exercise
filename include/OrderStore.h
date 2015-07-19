#ifndef ORDER_STORE_H
#define ORDER_STORE_H

#include <map>

#include "include/Order.h"
#include "include/exceptions.h"

class OrderStore {
    typedef std::map<long, OrderPtr> OrderMap;
    OrderMap store;
    long lastId;
    
public:
    OrderStore() : lastId(0) {}

    long put(OrderPtr& order) {
        long id = ++lastId;
        order->id(id);
        store.insert(std::make_pair(id, order));
        return id;
    }

    OrderPtr& get(long id) {
        return store.find(id)->second;
    }
};

#endif