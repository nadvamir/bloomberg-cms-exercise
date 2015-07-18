#ifndef DEALER_H
#define DEALER_H

#include "include/exceptions.h"

class Order {
public:
    enum Side { Buy, Sell };

private:
    Side side_;
    int quantity_;

public:
    Order(Side s, int q)
    : side_(s), quantity_(q) {
        if (q < 1) {
            throw InvalidMessage();
        }
    }

    Side side() const { return side_; }
    int quantity() { return quantity_; }
};


#endif
