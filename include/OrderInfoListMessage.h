#ifndef ORDER_INFO_LIST_MESSAGE_H
#define ORDER_INFO_LIST_MESSAGE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "include/Message.h" 
#include "include/OrderInfoMessage.h" 
#include "include/Order.h" 

class OrderInfoListMessage : public Message {
    typedef std::vector<OrderInfoMessage> OInfoCont;
    OInfoCont orders_;

protected:
    std::ostream& stream(std::ostream& o) const {
        // can't use copy trick because of trailing newlines :/
        OInfoCont::const_iterator it = orders_.begin();
        for (; it != orders_.end(); ++it) {
            o << *it << "\n";
        }
        return o << "END OF LIST";
    }

public:
    OrderInfoListMessage(std::vector<OrderPtr> orders) {
        copy(orders.begin(), orders.end(), back_inserter(orders_));
    }
};

#endif
