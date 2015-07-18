#include "gmock/gmock.h"

using namespace std;

class Commodity {
};
class Gold : public Commodity {
};

class Order {
public:
    Order(const Commodity &c) {}
};

TEST(AnOrder, IsCreatedForACommodity) {
    Gold g;
    Order subject(g);
}

