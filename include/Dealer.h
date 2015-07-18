#ifndef DEALER_H
#define DEALER_H

#include <iostream>
#include <string>
#include <algorithm>

#include "include/exceptions.h"

class Dealer {
    std::string id_;
    static const std::string dealers_[];
    static const size_t numDealers_;
public:
    Dealer(std::string id) : id_(id) {
        if (find(Dealer::dealers_,
                 Dealer::dealers_ + numDealers_,
                 id) == Dealer::dealers_ + numDealers_) {
            throw UnknownDealer();
        }
    }

    bool operator==(const Dealer& d) const {
        return id_ == d.id_;
    }

    friend std::ostream& operator<<(std::ostream& o,
                                    const Dealer &d) {
        return o << d.id_;
    }
};

const std::string Dealer::dealers_[] = {
    "DB", "JPM", "UBS", "RBC", "BARX", 
    "MS", "CITY", "BOFA", "RBS", "HSBC"
};
const size_t Dealer::numDealers_
    = sizeof Dealer::dealers_ / sizeof *Dealer::dealers_;

#endif
