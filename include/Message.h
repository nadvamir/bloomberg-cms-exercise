#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <sstream>
#include <string>

#include "include/SharedPtr.h" 

class Message;
typedef SharedPtr<Message> MessagePtr;

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

#endif
