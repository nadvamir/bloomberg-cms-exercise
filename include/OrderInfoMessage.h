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
    const std::string str() const {
        return order_;
    }

public:
    OrderInfoMessage(OrderPtr o) {
        std::stringstream ss;
        ss << *o << "\n";
        order_ = ss.str();
    }
};

#endif
