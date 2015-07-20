#include <map>
#include <algorithm>

#include "include/parsers.h"
#include "include/RevokeCommand.h"
#include "include/CheckCommand.h"

using namespace std;

namespace {

CommandPtr parseRevokeCommand(istream&);
CommandPtr parseCheckCommand(istream&);

typedef pair<string, CommandPtr (*)(istream&)> CallbackPair;
CallbackPair cmdParsers[] = {
    CallbackPair("REVOKE", parseRevokeCommand),
    CallbackPair("CHECK", parseCheckCommand)
};
size_t CMD_N = sizeof cmdParsers / sizeof *cmdParsers;

struct CallbackPred : public unary_function<CallbackPair, bool> {
    string cmd;
    CallbackPred(const string& c) : cmd(c) {}
    bool operator()(const CallbackPair& p) {
        return p.first == cmd;
    }
};

}

CommandPtr parseMessage(istream& in) {
    string dealerId, cmd;
    in >> dealerId >> cmd;
    CallbackPred pred(cmd);
    CallbackPair* cbk
        = find_if(cmdParsers, cmdParsers + CMD_N, pred);
    return cbk->second(in);
}

namespace {

CommandPtr parseRevokeCommand(istream& in) {
    return CommandPtr(new RevokeCommand(Dealer("JPM"), 1l));
}

CommandPtr parseCheckCommand(istream& in) {
    return CommandPtr(new CheckCommand(Dealer("JPM"), 1l));
}

}
