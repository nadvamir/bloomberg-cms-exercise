#include "gmock/gmock.h"

#include "include/Commodity.h"

using namespace std;

class Order {
public:
    Order(const Commodity &c) {}
};

TEST(AnOrder, IsCreatedForACommodity) {
    Gold g;
    Order subject(g);
}

