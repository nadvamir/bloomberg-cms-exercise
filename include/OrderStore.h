#ifndef ORDER_STORE_H
#define ORDER_STORE_H

#include <map>
#include <iterator>
#include <algorithm>
#include <vector>

#include "include/Order.h"
#include "include/SharedPtr.h"
#include "include/exceptions.h"
#include "include/CopyIf.h"

class OrderStore;
typedef SharedPtr<OrderStore, THREAD_SAFE> OrderStorePtr;

class OrderStore {
    typedef std::map<long, OrderPtr> OrderMap;
    typedef std::pair<long, OrderPtr> OrderPair;
    OrderMap store;
    long lastId;

public:
    OrderStore() : lastId(0) {}
    virtual ~OrderStore() {} // We need this class to be virtual
                             // for testing purposes

    virtual long put(OrderPtr& order);

    virtual OrderPtr& get(long id);

    virtual void remove(long id) {
        store.erase(id);
    }

    template<class UnaryPred>
    std::vector<OrderPtr> filter(UnaryPred pred);

private:
    static OrderPtr& pair2Order(OrderPair& el) {
        return el.second;
    }

    template<class UnaryPred>
    struct PredAdaptor;
};

template<class UnaryPred>
struct OrderStore::PredAdaptor {
    UnaryPred pred;
    PredAdaptor(UnaryPred p) : pred(p) {}
    bool operator()(OrderMap::value_type& el) {
        return pred(el.second);
    }
};

template<class UnaryPred>
std::vector<OrderPtr> OrderStore::filter(UnaryPred pred) {
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

#endif
