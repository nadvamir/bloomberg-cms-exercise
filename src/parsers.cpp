#include <map>
#include <algorithm>

#include "include/parsers.h"
#include "include/Dealer.h"
#include "include/RevokeCommand.h"
#include "include/CheckCommand.h"
#include "include/AggressCommand.h"

using namespace std;

namespace {

CommandPtr parseRevokeCommand(istream&, const Dealer&);
CommandPtr parseCheckCommand(istream&, const Dealer&);
CommandPtr parseAggressCommand(istream&, const Dealer&);

typedef pair<string, CommandPtr (*)(istream&, const Dealer&)>
        CallbackPair;
CallbackPair cmdParsers[] = {
    CallbackPair("REVOKE", parseRevokeCommand),
    CallbackPair("CHECK", parseCheckCommand),
    CallbackPair("AGGRESS", parseAggressCommand)
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

    Dealer dealer(dealerId);
    CallbackPred pred(cmd);

    CallbackPair* cbk
        = find_if(cmdParsers, cmdParsers + CMD_N, pred);
    if (cbk == cmdParsers + CMD_N) {
        throw InvalidMessage();
    }

    return cbk->second(in, dealer);
}

namespace {

CommandPtr parseRevokeCommand(istream& in, const Dealer& d) {
    long id; in >> id;
    return CommandPtr(new RevokeCommand(d, id));
}

CommandPtr parseCheckCommand(istream& in, const Dealer& d) {
    long id; in >> id;
    return CommandPtr(new CheckCommand(d, id));
}

CommandPtr parseAggressCommand(istream& in, const Dealer&) {
    long id; in >> id;
    int amount; in >> amount;
    return CommandPtr(new AggressCommand(id, amount));
}


}
