#include "gmock/gmock.h"

#include <iterator>
#include <vector>
#include <map>

#include "include/CopyIf.h"

using namespace testing;
using namespace std;

namespace {
bool isEven(int num) { return num % 2 == 0; }
bool valEven(pair<const int, int> &el) {
    return el.second % 2 == 0;
}
}

TEST(ACopyIf, CopiesElementsIfTheyMatchAPredicate) {
    int vals[] = {4, 5, 5, 4};

    int evenVals[] = {4, 4};
    vector<int> even;
    copy(evenVals, evenVals + 2, back_inserter(even));

    vector<int> result;

    copy_if(vals, vals + 4, back_inserter(result), isEven);

    ASSERT_THAT(result, Eq(even));
}

TEST(ACopyIf, CopiesElementsBetweenDifferentContainers) {
    map<int, int> m;
    m.insert(make_pair(1, 1));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(3, 3));
    vector<pair<int, int> > v;

    copy_if(m.begin(), m.end(), back_inserter(v), valEven);

    ASSERT_THAT(v.size(), Eq(1));
    ASSERT_THAT(v[0].second, Eq(2));
}

