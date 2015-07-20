#ifndef COMMAND_H
#define COMMAND_H

#include <include/Message.h>
#include <include/OrderStore.h>

class Command {
public:
    virtual ~Command() {}
    virtual MessagePtr operator()(OrderStorePtr store) = 0;
};

#endif
