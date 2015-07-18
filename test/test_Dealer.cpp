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
    Dealer jp("JP"), jp2("JP");
    ASSERT_THAT(test_compare(jp, jp2), Eq(true));
}

TEST_F(ADealer, DealersFromDifferentCompaniesAreNotEqual) {
    Dealer jp("JP"), barx("BARX");
    ASSERT_THAT(test_compare(jp, barx), Eq(false));
}

TEST_F(ADealer, CanOnlyBeCreatedForSpecifiedCompanies) {
    ASSERT_NO_THROW({ Dealer("JP"); });
    ASSERT_THROW(Dealer("MAXBANK"), UnknownDealer);
}
