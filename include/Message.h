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
    virtual std::ostream& stream(std::ostream& o) const = 0;

public:
    virtual ~Message() {}
    friend std::ostream& operator<<(std::ostream& o,
                                    const Message& m) {
        return m.stream(o);
    }
};

#endif
