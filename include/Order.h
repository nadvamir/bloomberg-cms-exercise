#ifndef ORDER_H
#define ORDER_H

#include <memory>

#include "include/Dealer.h"
#include "include/Commodity.h"
#include "include/exceptions.h"

class Order {
public:
    enum Side { Buy, Sell };
    enum { NoID = -1 };

private:
    int id_;
    Dealer dealer_;
    std::auto_ptr<Commodity> commodity_;
    Side side_;
    int quantity_;
    double price_;

public:
    Order(Dealer d, Side s,
          std::auto_ptr<Commodity> c ,int q, double p)
    : id_(Order::NoID), dealer_(d), commodity_(c)
    , side_(s), quantity_(q), price_(p) {
        if (q < 1 || p <= 0.0) {
            throw InvalidMessage();
        }
    }

    Side side() const { return side_; }
    int quantity() const { return quantity_; }
    int id() const { return id_; }

    void id(int i) { id_ = i; }

    void aggress(int q) {
        if (q > quantity_) {
            throw InvalidMessage();
        }
        quantity_ -= q;
    }
};

#endif
