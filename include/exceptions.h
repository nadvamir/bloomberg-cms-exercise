#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

class UnknownOrder : public std::runtime_error {
public:
    UnknownOrder() : std::runtime_error("UNKNOWN_ORDER") {}
};

class UnknownDealer : public std::runtime_error {
public:
    UnknownDealer() : std::runtime_error("UNKNOWN_DEALER") {}
};

class InvalidMessage : public std::runtime_error {
public:
    InvalidMessage() : std::runtime_error("INVALID_MESSAGE") {}
};

#endif
