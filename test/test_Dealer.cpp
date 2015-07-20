#include "gmock/gmock.h"

#include "include/Dealer.h"
#include "include/exceptions.h"

#include <sstream>

using namespace testing;
using namespace std;

class ADealer : public Test {
public:
    bool test_compare(const Dealer& c1, const Dealer& c2) {
        return c1 == c2;
    }
};

TEST_F(ADealer, DealersOfTheSameCompanyAreEqual) {
    Dealer jp("JPM"), jp2("JPM");
    ASSERT_THAT(test_compare(jp, jp2), Eq(true));
}

TEST_F(ADealer, DealersFromDifferentCompaniesAreNotEqual) {
    Dealer jp("JPM"), barx("BARX");
    ASSERT_THAT(test_compare(jp, barx), Eq(false));
}

TEST_F(ADealer, SupportsNotEqOperator) {
    Dealer jp("JPM"), barx("BARX");
    ASSERT_THAT(jp != barx, Eq(true));
}

TEST_F(ADealer, CanOnlyBeCreatedForSpecifiedCompanies) {
    ASSERT_NO_THROW({ Dealer("JPM"); });
    ASSERT_THROW(Dealer("MAXBANK"), UnknownDealer);
}

TEST_F(ADealer, StreamsItsId) {
    Dealer jp("JPM");
    stringstream ss;

    ss << jp;

    ASSERT_THAT(ss.str(), StrEq("JPM"));
}
