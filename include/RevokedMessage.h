#ifndef REVOKED_MESSAGE_H
#define REVOKED_MESSAGE_H

#include <iostream>
#include <sstream>
#include <string>

#include "include/Message.h" 

class RevokedMessage : public Message {
    long id_;

protected:
    const std::string str() const {
        std::stringstream ss;
        ss << id_ << " HAS BEEN REVOKED\n";
        return ss.str();
    }

public:
    RevokedMessage(long id) : id_(id) {}
};

#endif
