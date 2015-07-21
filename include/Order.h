#ifndef ORDER_H
#define ORDER_H

#include <iostream>

#include "include/Dealer.h"
#include "include/Commodity.h"
#include "include/exceptions.h"
#include "include/SharedPtr.h"

class Order;
typedef SharedPtr<Order, true> OrderPtr;

class Order {
public:
    enum Side { Buy, Sell };
    enum { NoID = -1 };

private:
    int id_;
    Dealer dealer_;
    CommodityPtr commodity_;
    Side side_;
    int quantity_;
    double price_;

public:
    Order(Dealer d, Side s,
          CommodityPtr c ,int q, double p)
    : id_(Order::NoID), dealer_(d), commodity_(c)
    , side_(s), quantity_(q), price_(p) {
        if (q < 1 || p <= 0.0) {
            throw InvalidMessage();
        }
    }

    int id() const { return id_; }
    const Dealer& dealer() const { return dealer_; }
    const CommodityPtr& commodity() const { return commodity_; }
    Side side() const { return side_; }
    int quantity() const { return quantity_; }
    double price() const { return price_; }
    bool isFilled() const { return quantity_ == 0; }

    void id(int i) { id_ = i; }

    void aggress(int q) {
        if (q > quantity_) {
            throw InvalidMessage();
        }
        quantity_ -= q;
    }

    friend std::ostream& operator<<(std::ostream& o,
                                    const Order& ord) {
        o   << ord.id_ << " "
            << ord.dealer_ << " "
            << ((ord.side_ == Buy) ? "BUY" : "SELL") << " "
            << *ord.commodity_ << " "
            << ord.quantity_ << " "
            << ord.price_;
        return o;
    }
};

#endif
