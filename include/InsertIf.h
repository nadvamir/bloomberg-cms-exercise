#ifndef INSERT_IF_H
#define INSERT_IF_H

#include <functional>

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

#endif
