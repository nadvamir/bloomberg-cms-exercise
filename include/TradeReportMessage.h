#ifndef TRADE_REPORT_MESSAGE_H
#define TRADE_REPORT_MESSAGE_H

#include <iostream>
#include <sstream>
#include <string>

#include "include/Message.h" 
#include "include/Order.h" 

class TradeReportMessage : public Message {
    std::string order_;

protected:
    std::ostream& stream(std::ostream& o) const {
        return o << order_;
    }

public:
    TradeReportMessage(OrderPtr o) {
        std::stringstream ss;
        ss  << ((o->side() == Order::Buy) ? "BOUGHT " : "SOLD ")
            << o->quantity() << " "
            << *(o->commodity()) << " @ "
            << o->price() << " FROM "
            << o->dealer();
        order_ = ss.str();
    }
};

#endif
