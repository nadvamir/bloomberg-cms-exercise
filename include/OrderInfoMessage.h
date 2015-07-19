#ifndef ORDER_INFO_MESSAGE_H
#define ORDER_INFO_MESSAGE_H

#include <iostream>
#include <sstream>
#include <string>

#include "include/Message.h" 
#include "include/Order.h" 

class OrderInfoMessage : public Message {
    std::string order_;

protected:
    std::ostream& stream(std::ostream& o) const {
        return o << order_;
    }

public:
    OrderInfoMessage(OrderPtr o) {
        std::stringstream ss;
        ss << *o;
        order_ = ss.str();
    }
};

#endif
