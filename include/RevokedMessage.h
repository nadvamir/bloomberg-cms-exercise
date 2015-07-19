#ifndef REVOKED_MESSAGE_H
#define REVOKED_MESSAGE_H

#include <iostream>
#include <string>

#include "include/Message.h" 

class RevokedMessage : public Message {
    long id_;

protected:
    std::ostream& stream(std::ostream& o) const {
        return o << id_ << " HAS BEEN REVOKED";
    }

public:
    RevokedMessage(long id) : id_(id) {}
};

#endif
