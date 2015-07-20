#ifndef REVOKE_COMMAND_H
#define REVOKE_COMMAND_H

#include "include/Command.h"
#include "include/RevokedMessage.h"
#include "include/Dealer.h"
#include "include/exceptions.h"

class RevokeCommand : public Command {
    Dealer dealer_;
    long orderId_;
public:
    RevokeCommand(const Dealer& dealer, long orderId)
    : dealer_(dealer), orderId_(orderId) {}

    MessagePtr operator()(OrderStorePtr store) {
        OrderPtr order = store->get(orderId_);
        if (order->dealer() != dealer_) {
            throw Unauthorized();
        }

        store->remove(orderId_);

        return MessagePtr(new RevokedMessage(orderId_));
    }

    bool operator==(const RevokeCommand& cmd) const {
        return dealer_ == cmd.dealer_ && orderId_ == cmd.orderId_;
    }
};

#endif
