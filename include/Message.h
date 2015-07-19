#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <sstream>
#include <string>

#include "include/SharedPtr.h" 

class Message {
protected:
    virtual const std::string str() const {
        return "BASE\n";
    }

public:
    virtual ~Message() {}
    friend std::ostream& operator<<(std::ostream& o,
                                    const Message& m) {
        return o << m.str();
    }
};

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
