#include "gmock/gmock.h"

#include <iterator>
#include <vector>

#include "include/InsertIf.h"

using namespace testing;
using namespace std;

bool even(int num) { return num % 2 == 0; }

TEST(AnInsertIf, CopiesElementsIfTheyMatchAPredicate) {
    int vals[] = {4, 5, 5, 4};
    int evenVals[] = {4, 4};

    vector<int> valv;
    copy(vals, vals + 4, back_inserter(valv));
    vector<int> evenValv;
    copy(evenVals, evenVals + 2, back_inserter(evenValv));

    vector<int> evenv;
    InsertIf<int, bool (*)(int),
             back_insert_iterator<vector<int> >
    > iif(even, back_inserter(evenv));

    for_each(vals, vals + 4, iif);

    ASSERT_THAT(evenv, Eq(evenValv));
}

TEST(AnInsertIf, CanBeCreatedWithTypesDeduced) {
    int vals[] = {4, 5, 5, 4};
    int evenVals[] = {4, 4};

    vector<int> valv;
    copy(vals, vals + 4, back_inserter(valv));
    vector<int> evenValv;
    copy(evenVals, evenVals + 2, back_inserter(evenValv));

    vector<int> evenv;

    for_each(vals, vals + 4,
             IfInserter<int>::make(even, back_inserter(evenv)));

    ASSERT_THAT(evenv, Eq(evenValv));
}
