#ifndef LIST_COMMAND_H
#define LIST_COMMAND_H

#include <functional>

#include "include/Command.h"
#include "include/OrderInfoListMessage.h"
#include "include/Dealer.h"
#include "include/Commodity.h"
#include "include/exceptions.h"

namespace {
bool showAll(OrderPtr) { return true; }
}

struct CommodityPred : public std::unary_function<OrderPtr, bool> {
    CommodityPtr commodity;
    CommodityPred(CommodityPtr c) : commodity(c) {}
    bool operator()(const OrderPtr& o) const {
        return *commodity == *(o->commodity());
    }
};

// I miss lambdas so much...
struct CommodityAndDealerPred
: public std::unary_function<OrderPtr, bool> {
    CommodityPtr commodity;
    Dealer dealer;
    CommodityAndDealerPred(CommodityPtr c, const Dealer& d)
    : commodity(c), dealer(d) {}
    bool operator()(const OrderPtr& o) const {
        return *commodity == *(o->commodity())
               && dealer == o->dealer();
    }
};

class ListCommand : public Command {
    CommodityPtr commodity_;
    Dealer dealer_;
public:
    ListCommand() {}
    ListCommand(CommodityPtr c) : commodity_(c) {}
    ListCommand(CommodityPtr c, const Dealer& d)
    : commodity_(c), dealer_(d) {}

    MessagePtr operator()(OrderStorePtr store) {
        if (!commodity_.isNull() && !(dealer_ == Dealer())) {
            return MessagePtr(new OrderInfoListMessage(
                store->filter(CommodityAndDealerPred(
                    commodity_, dealer_))));
        }
        else if (!commodity_.isNull()) {
            return MessagePtr(new OrderInfoListMessage(
                store->filter(CommodityPred(commodity_))));
        }
        return MessagePtr(new OrderInfoListMessage(
            store->filter(showAll)));
    }
};

#endif
