#ifndef AGGRESS_COMMAND_H
#define AGGRESS_COMMAND_H

#include "include/Command.h"
#include "include/TradeReportMessage.h"
#include "include/exceptions.h"

class AggressCommand : public Command {
    long orderId_;
    int amount_;
public:
    AggressCommand(long orderId, int amount)
    : orderId_(orderId), amount_(amount) {}

    MessagePtr operator()(OrderStorePtr store) {
        OrderPtr order = store->get(orderId_);

        order->aggress(amount_);

        return MessagePtr();
    }
};

#endif
