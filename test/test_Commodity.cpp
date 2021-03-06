#include "gmock/gmock.h"

#include "include/Commodity.h"

#include <sstream>

using namespace testing;
using namespace std;

class ACommodity : public Test {
public:
    bool test_compare(const Commodity& c1, const Commodity& c2) {
        return c1 == c2;
    }
};

TEST_F(ACommodity, CommoditiesOfTheSameTypeAreEqual) {
    Gold g1, g2;
    ASSERT_THAT(test_compare(g1, g2), Eq(true));
}

TEST_F(ACommodity, DifferentCommoditiesAreNotEqual) {
    Gold g;
    Silver s;
    ASSERT_THAT(test_compare(g, s), Eq(false));
}

TEST_F(ACommodity, PrintsItsNameToAStreamThroughAParentPointer) {
    Gold g;
    Commodity* p = &g;
    stringstream ss;

    ss << *p;

    ASSERT_THAT(ss.str(), StrEq("GOLD"));
}

TEST_F(ACommodity, AllSpecifiedCommoditiesAreDefined) {
    stringstream ss;

    ss  << Gold() << " "
        << Silver() << " "
        << Pork() << " "
        << Oil() << " "
        << Rice();

    ASSERT_THAT(ss.str(), StrEq("GOLD SILV PORK OIL RICE"));
}
