#include "include/Dealer.h"

const std::string Dealer::dealers_[] = {
    "DB", "JPM", "UBS", "RBC", "BARX", 
    "MS", "CITI", "BOFA", "RBS", "HSBC"
};
const size_t Dealer::numDealers_
    = sizeof Dealer::dealers_ / sizeof *Dealer::dealers_;

