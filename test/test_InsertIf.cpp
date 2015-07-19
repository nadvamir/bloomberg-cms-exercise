#include "gmock/gmock.h"

#include <functional>
#include <iterator>
#include <vector>

using namespace testing;
using namespace std;

template<class ArgType, class Pred, class Inserter>
class InsertIf : public std::unary_function<ArgType, void> {
    Pred pred_;
    Inserter inserter_;
public:
    InsertIf(Pred p, Inserter i) : pred_(p), inserter_(i) {}
    void operator()(const ArgType& item) {
        if (pred_(item)) {
            *inserter_ = item;
        }
    }
};

template<class Element>
struct IfInserter {
    template<class Pred, class Inserter>
    static InsertIf<Element, Pred, Inserter>
    make(Pred pred, Inserter inserter) {
        return InsertIf<Element, Pred, Inserter>(pred, inserter);
    }
};

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
