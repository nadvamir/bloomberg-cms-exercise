#ifndef LIST_COMMAND_H
#define LIST_COMMAND_H

#include <functional>

#include "include/Command.h"
#include "include/OrderInfoListMessage.h"
#include "include/Dealer.h"
#include "include/Commodity.h"
#include "include/exceptions.h"

namespace {
bool showAll(const OrderPtr& o) { return !o->isFilled(); }
}

struct CommodityPred : public std::unary_function<OrderPtr, bool> {
    CommodityPtr commodity;
    CommodityPred(CommodityPtr c) : commodity(c) {}
    bool operator()(const OrderPtr& o) const {
        return *commodity == *(o->commodity()) && !o->isFilled();
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
               && dealer == o->dealer() && !o->isFilled();
    }
};

class ListCommand : public Command {
    CommodityPtr commodity_;
    Dealer dealer_;
public:
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

    bool operator==(const ListCommand& cmd) const {
        return ((commodity_.isNull() && cmd.commodity_.isNull())
            || (!commodity_.isNull() && !cmd.commodity_.isNull()
                && *commodity_ == *(cmd.commodity_)))
            && dealer_ == cmd.dealer_;
    }
};

#endif
