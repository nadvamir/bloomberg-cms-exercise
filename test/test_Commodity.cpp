#include "gmock/gmock.h"

using namespace testing;
using namespace std;

class Gold;
class Commodity {
public:
    virtual bool eq(const Gold&) const = 0;
    virtual bool eq(const Commodity&) const { return false; }
    virtual bool operator==(const Commodity& c) const {
        return c.eq(*this);
    }
};

class Gold : public Commodity {
public:
    bool eq(const Gold&) const { return true; }
    bool operator==(const Commodity& c) const {
        return c.eq(*this);
    }
};

class Silver : public Commodity {
};

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

