#ifndef DEALER_H
#define DEALER_H

#include <iostream>
#include <string>

class Dealer {
    std::string id_;
public:
    Dealer(std::string id) : id_(id) {}

    bool operator==(const Dealer& d) const {
        return id_ == d.id_;
    }
};

#endif
