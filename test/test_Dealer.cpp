#include "gmock/gmock.h"

#include "include/Dealer.h"

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
    Dealer jp("JP"), barx("JP");
    ASSERT_THAT(test_compare(jp, barx), Eq(true));
}

