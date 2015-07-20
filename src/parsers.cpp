#include <map>
#include <algorithm>
#include <stdexcept>

#include "include/parsers.h"
#include "include/Dealer.h"
#include "include/RevokeCommand.h"
#include "include/CheckCommand.h"
#include "include/AggressCommand.h"
#include "include/PostCommand.h"
#include "include/ListCommand.h"
#include "include/exceptions.h"

using namespace std;

namespace {

CommandPtr parseRevokeCommand(istream&, const Dealer&);
CommandPtr parseCheckCommand(istream&, const Dealer&);
CommandPtr parseAggressCommand(istream&, const Dealer&);
CommandPtr parsePostCommand(istream&, const Dealer&);
CommandPtr parseListCommand(istream&, const Dealer&);

typedef pair<string, CommandPtr (*)(istream&, const Dealer&)>
        CallbackPair;
CallbackPair cmdParsers[] = {
    CallbackPair("REVOKE", parseRevokeCommand),
    CallbackPair("CHECK", parseCheckCommand),
    CallbackPair("AGGRESS", parseAggressCommand),
    CallbackPair("POST", parsePostCommand),
    CallbackPair("LIST", parseListCommand)
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
    in.exceptions(istream::failbit | istream::badbit);
    string dealerId, cmd;

    try { in >> dealerId >> cmd; }
    catch (istream::failure& e) { throw InvalidMessage(); }

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
    long id;

    try { in >> id; }
    catch (istream::failure& e) { throw InvalidMessage(); }

    return CommandPtr(new RevokeCommand(d, id));
}

CommandPtr parseCheckCommand(istream& in, const Dealer& d) {
    long id;

    try { in >> id; }
    catch (istream::failure& e) { throw InvalidMessage(); }

    return CommandPtr(new CheckCommand(d, id));
}

CommandPtr parseAggressCommand(istream& in, const Dealer&) {
    long id;
    int amount;

    try { in >> id >> amount; }
    catch (istream::failure& e) { throw InvalidMessage(); }

    return CommandPtr(new AggressCommand(id, amount));
}

CommandPtr parsePostCommand(istream& in, const Dealer& dealer) {
    string sside, scommodity;
    int amount; double price;

    try { in >> sside >> scommodity >> amount >> price; }
    catch (istream::failure& e) { throw InvalidMessage(); }

    Order::Side side = (sside == "BUY") ? Order::Buy : Order::Sell;
    CommodityPtr commodity(getCommodity(scommodity));

    return CommandPtr(new PostCommand(
        dealer, side, commodity, amount, price));
}

CommandPtr parseListCommand(istream& in, const Dealer&) {
    CommodityPtr commodity;
    Dealer dealer;
    
    try {
        string scommodity, dealerId;
        if (in >> scommodity) {
            commodity = getCommodity(scommodity);
        }

        if (in >> dealerId) {
            dealer = Dealer(dealerId);
        }
    }
    catch (istream::failure& e) {} // generous with list parsing

    return CommandPtr(new ListCommand(commodity, dealer));
}

}
