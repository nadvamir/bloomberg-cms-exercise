#include "include/parsers.h"
#include "include/RevokeCommand.h"

CommandPtr parseMessage(std::ostream& o) {
    return CommandPtr(new RevokeCommand(Dealer("JPM"), 1l));
}
