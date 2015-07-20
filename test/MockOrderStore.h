#ifndef MOCK_ORDER_STORE_H
#define MOCK_ORDER_STORE_H

#include "gmock/gmock.h"

#include "include/Order.h"
#include "include/OrderStore.h"

class MockOrderStore : public OrderStore {
public:
    MOCK_METHOD1(put, long(OrderPtr&));

    MOCK_METHOD1(get, OrderPtr&(long));

    MOCK_METHOD1(remove, void(long));

    // filter will have to be used for a real object
};

#endif
