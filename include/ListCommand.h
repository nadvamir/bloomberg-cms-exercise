#ifndef LIST_COMMAND_H
#define LIST_COMMAND_H

#include <functional>

#include "include/Command.h"
#include "include/OrderInfoListMessage.h"
#include "include/Dealer.h"
#include "include/Commodity.h"
#include "include/exceptions.h"

struct CommodityPred : public std::unary_function<OrderPtr, bool> {
    CommodityPtr commodity;
    CommodityPred(CommodityPtr c) : commodity(c) {}
    bool operator()(const OrderPtr& o) const {
        return *commodity == *(o->commodity());
    }
};

class ListCommand : public Command {
    Dealer dealer_;
    long orderId_;
public:
    ListCommand(const Dealer& dealer, long orderId)
    : dealer_(dealer), orderId_(orderId) {}

    MessagePtr operator()(OrderStorePtr store) {
        OrderPtr order = store->get(orderId_);
        if (order->dealer() != dealer_) {
            throw Unauthorized();
        }

        store->remove(orderId_);

        return MessagePtr();
    }
};

#endif
