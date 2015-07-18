#ifndef ORDER_H
#define ORDER_H

#include <memory>

#include "include/Dealer.h"
#include "include/Commodity.h"
#include "include/exceptions.h"

class Order {
public:
    enum Side { Buy, Sell };

private:
    Side side_;
    int quantity_;
    double price_;

public:
    Order(Dealer d, Side s,
          std::auto_ptr<Commodity> c ,int q, double p)
    : side_(s), quantity_(q), price_(p) {
        if (q < 1 || p <= 0.0) {
            throw InvalidMessage();
        }
    }

    Side side() const { return side_; }
    int quantity() { return quantity_; }
};

#endif
