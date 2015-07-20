#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

class Unauthorized : public std::runtime_error {
public:
    Unauthorized() : std::runtime_error("UNAUTHORIZED") {}
};

class UnknownOrder : public std::runtime_error {
public:
    UnknownOrder() : std::runtime_error("UNKNOWN_ORDER") {}
};

class UnknownCommodity : public std::runtime_error {
public:
    UnknownCommodity() : std::runtime_error("UNKNOWN_COMMODITY") {}
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
