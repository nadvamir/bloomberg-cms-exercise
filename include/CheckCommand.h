#ifndef CHECK_COMMAND_H
#define CHECK_COMMAND_H

#include "include/Command.h"
#include "include/OrderInfoMessage.h"
#include "include/FilledMessage.h"
#include "include/Dealer.h"
#include "include/exceptions.h"

class CheckCommand : public Command {
    Dealer dealer_;
    long orderId_;
public:
    CheckCommand(const Dealer& dealer, long orderId)
    : dealer_(dealer), orderId_(orderId) {}

    MessagePtr operator()(OrderStorePtr store) {
        OrderPtr order = store->get(orderId_);
        if (order->dealer() != dealer_) {
            throw Unauthorized();
        }

        if (order->isFilled()) {
            return MessagePtr(new FilledMessage(orderId_));
        }

        return MessagePtr(new OrderInfoMessage(order));
    }
};

#endif
