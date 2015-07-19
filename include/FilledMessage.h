#ifndef FILLED_MESSAGE_H
#define FILLED_MESSAGE_H

#include <iostream>
#include <string>

#include "include/Message.h" 

class FilledMessage : public Message {
    long id_;

protected:
    std::ostream& stream(std::ostream& o) const {
        return o << id_ << " HAS BEEN FILLED";
    }

public:
    FilledMessage(long id) : id_(id) {}
};

#endif
