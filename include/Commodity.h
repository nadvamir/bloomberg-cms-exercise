#ifndef COMMODITY_H
#define COMMODITY_H

class Commodity {
public:
    virtual bool operator==(const Commodity& c) const {
        return typeid(*this) == typeid(c);
    }
};

class Gold : public Commodity {
};

class Silver : public Commodity {
};

#endif
