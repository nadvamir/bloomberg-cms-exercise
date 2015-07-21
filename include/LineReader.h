#ifndef LINE_READER_H
#define LINE_READER_H

#include <iostream>
#include <string>

#include "include/SharedPtr.h"

class LineReader;
typedef SharedPtr<LineReader> LineReaderPtr;

class LineReader {
public:
    virtual ~LineReader() {}
    virtual bool getline(std::string& line) = 0;
};

class StreamLineReader : public LineReader {
    std::istream& stream_;
public:
    StreamLineReader(std::istream &s) : stream_(s) {}

    bool getline(std::string& line) {
        return std::getline(stream_, line);
    }
};

#endif
