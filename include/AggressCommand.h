#ifndef AGGRESS_COMMAND_H
#define AGGRESS_COMMAND_H

#include "include/Command.h"
#include "include/TradeReportMessage.h"
#include "include/Order.h"
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

        // order for reporting this trade
        OrderPtr aggression(new Order(
            order->dealer(),
            opposite(order->side()),
            order->commodity(), amount_, order->price()));

        return MessagePtr(new TradeReportMessage(aggression));
    }

private:
    Order::Side opposite(Order::Side side) {
        return (side == Order::Buy) ? Order::Sell : Order::Buy;
    }
};

#endif
