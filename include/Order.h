#ifndef DEALER_H
#define DEALER_H

#include "include/exceptions.h"

class Order {
public:
    enum Side { Buy, Sell };

private:
    Side side_;
    int quantity_;
    double price_;

public:
    Order(Side s, int q, double p)
    : side_(s), quantity_(q), price_(p) {
        if (q < 1 || p <= 0.0) {
            throw InvalidMessage();
        }
    }

    Side side() const { return side_; }
    int quantity() { return quantity_; }
};

#endif
