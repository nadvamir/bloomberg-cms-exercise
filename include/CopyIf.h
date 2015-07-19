#ifndef COPY_IF_H
#define COPY_IF_H

template<
    class InputIterator,
    class OutputIterator,
    class Predicate>
void copy_if(InputIterator first,
             InputIterator last,
             OutputIterator out,
             Predicate pred) {
    for (; first != last; ++first) {
        if (pred(*first)) {
            *out++ = *first;
        }
    }
}

#endif
