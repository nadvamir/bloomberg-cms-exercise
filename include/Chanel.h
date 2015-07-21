#ifndef CHANEL_H
#define CHANEL_H

#include <iostream>
#include <string>

#include "include/SharedPtr.h"

class Chanel;
typedef SharedPtr<Chanel> ChanelPtr;

const int MAX_LINE = 255;

class Chanel {
public:
    virtual ~Chanel() {}
    virtual bool getline(std::string& line) = 0;
    virtual void putline(const std::string& line) = 0;
};

class StreamChanel : public Chanel {
    std::istream& istream_;
    std::ostream& ostream_;
public:
    StreamChanel(std::istream& is, std::ostream& os)
    : istream_(is), ostream_(os) {}

    bool getline(std::string& line) {
        return std::getline(istream_, line);
    }

    void putline(const std::string& line) {
        ostream_ << line << std::endl;
    }
};

#endif
