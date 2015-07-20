#ifndef ORDER_STORE_H
#define ORDER_STORE_H

#include <map>
#include <iterator>
#include <algorithm>
#include <vector>

#include "include/Order.h"
#include "include/exceptions.h"
#include "include/CopyIf.h"
#include "include/SharedPtr.h"

class OrderStore;
typedef SharedPtr<OrderStore> OrderStorePtr;

class OrderStore {
    typedef std::map<long, OrderPtr> OrderMap;
    typedef std::pair<long, OrderPtr> OrderPair;
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
        OrderMap::iterator it = store.find(id);
        if (it == store.end()) {
            throw UnknownOrder();
        }
        return it->second;
    }

    void remove(long id) {
        store.erase(id);
    }

    template<class UnaryPred>
    std::vector<OrderPtr> filter(UnaryPred pred) {
        std::vector<OrderPair> filtered;
        copy_if(
            store.begin(),
            store.end(),
            back_inserter(filtered),
            PredAdaptor<UnaryPred>(pred));

        std::vector<OrderPtr> orders;
        transform(
            filtered.begin(),
            filtered.end(),
            back_inserter(orders),
            OrderStore::pair2Order);

        return orders;
    }

private:
    static OrderPtr& pair2Order(OrderPair& el) {
        return el.second;
    }

    template<class UnaryPred>
    struct PredAdaptor {
        UnaryPred pred;
        PredAdaptor(UnaryPred p) : pred(p) {}
        bool operator()(OrderMap::value_type& el) {
            return pred(el.second);
        }
    };
};

#endif
