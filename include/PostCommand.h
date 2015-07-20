#ifndef POST_COMMAND_H
#define POST_COMMAND_H

#include "include/Command.h"
#include "include/PostConfirmationMessage.h"
#include "include/Order.h"
#include "include/exceptions.h"

class PostCommand : public Command {
    Dealer dealer_;
    Order::Side side_;
    CommodityPtr commodity_;
    int amount_;
    double price_;
public:
    PostCommand(Dealer d, Order::Side s, CommodityPtr c,
                int a, double p)
    : dealer_(d), side_(s), commodity_(c), amount_(a), price_(p) {}

    MessagePtr operator()(OrderStorePtr store) {
        OrderPtr order(new Order(
            dealer_, side_, commodity_, amount_, price_));

        store->put(order);

        return MessagePtr(new PostConfirmationMessage(order));
    }

private:
    Order::Side opposite(Order::Side side) {
        return (side == Order::Buy) ? Order::Sell : Order::Buy;
    }
};

#endif
