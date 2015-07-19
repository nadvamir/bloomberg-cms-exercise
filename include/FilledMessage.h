#ifndef FILLED_MESSAGE_H
#define FILLED_MESSAGE_H

#include <iostream>
#include <sstream>
#include <string>

#include "include/Message.h" 

class FilledMessage : public Message {
    long id_;

protected:
    const std::string str() const {
        std::stringstream ss;
        ss << id_ << " HAS BEEN FILLED\n";
        return ss.str();
    }

public:
    FilledMessage(long id) : id_(id) {}
};

#endif
