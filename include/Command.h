#ifndef COMMAND_H
#define COMMAND_H

#include <include/Message.h>
#include <include/OrderStore.h>
#include <include/SharedPtr.h>

class Command;
typedef SharedPtr<Command> CommandPtr;

class Command {
public:
    virtual ~Command() {}
    virtual MessagePtr operator()(OrderStorePtr store) = 0;
};

#endif
