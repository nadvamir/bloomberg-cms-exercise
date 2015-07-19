#ifndef POST_CONFIRMATION_MESSAGE_H
#define POST_CONFIRMATION_MESSAGE_H

#include <iostream>
#include <string>

#include "include/Message.h" 
#include "include/OrderInfoMessage.h" 
#include "include/Order.h" 

class PostConfirmationMessage : public Message {
    OrderInfoMessage orderInfo_;

protected:
    std::ostream& stream(std::ostream& o) const {
        return o << orderInfo_ << " HAS BEEN POSTED";
    }

public:
    PostConfirmationMessage(OrderPtr o) : orderInfo_(o) {} 
};

#endif
