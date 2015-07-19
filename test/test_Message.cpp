#include "gmock/gmock.h"

#include <iostream>
#include <sstream>
#include <string>

#include "include/SharedPtr.h"

using namespace std;

class Message {
protected:
    virtual const std::string str() const {
        return "BASE\n";
    }

public:
    virtual ~Message() {}
    friend ostream& operator<<(ostream& o,
                               const Message& m) {
        return o << m.str();
    }
};

class FilledMessage : public Message {
    long id_;

protected:
    const std::string str() const {
        stringstream ss;
        ss << id_ << " HAS BEEN FILLED\n";
        return ss.str();
    }

public:
    FilledMessage(long id) : id_(id) {}
};

TEST(AMessage, CanBeStreamedThroughAParentObject) {
    FilledMessage fm(10);
    Message& m = fm;
    stringstream ss;

    ss << m;

    ASSERT_THAT(ss.str(), testing::StrEq("10 HAS BEEN FILLED\n"));
}
