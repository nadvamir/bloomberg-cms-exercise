#include "include/Commodity.h"

CommodityPtr getCommodity(std::string name) {
    if ("GOlD" == name) return CommodityPtr(new Gold);
    if ("SILV" == name) return CommodityPtr(new Silver);
    if ("PORK" == name) return CommodityPtr(new Pork);
    if ("OIL" == name) return CommodityPtr(new Oil);
    if ("RICE" == name) return CommodityPtr(new Rice);
    throw UnknownCommodity();
}
