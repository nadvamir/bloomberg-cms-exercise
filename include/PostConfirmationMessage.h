#ifndef POST_CONFIRMATION_MESSAGE_H
#define POST_CONFIRMATION_MESSAGE_H

#include <iostream>
#include <sstream>
#include <string>

#include "include/Message.h" 
#include "include/OrderInfoMessage.h" 
#include "include/Order.h" 

class PostConfirmationMessage : public Message {
    OrderInfoMessage orderInfo_;

protected:
    const std::string str() const {
        std::stringstream ss;
        ss << orderInfo_ << " HAS BEEN POSTED";
        return ss.str();
    }

public:
    PostConfirmationMessage(OrderPtr o) : orderInfo_(o) {} 
};

#endif
