#ifndef COMMODITY_H
#define COMMODITY_H

#include <iostream>

class Commodity {
    virtual const char* getTag() const = 0;
public:
    virtual bool operator==(const Commodity& c) const {
        return typeid(*this) == typeid(c);
    }

    friend std::ostream& operator<<(std::ostream& o, const Commodity& c) {
        o << c.getTag();
        return o;
    }
};

class Gold : public Commodity {
    virtual const char* getTag() const { return "GOLD"; }
};

class Silver : public Commodity {
    virtual const char* getTag() const { return "SILV"; }
};

class Pork : public Commodity {
    virtual const char* getTag() const { return "PORK"; }
};

class Oil : public Commodity {
    virtual const char* getTag() const { return "OIL"; }
};

class Rice : public Commodity {
    virtual const char* getTag() const { return "RICE"; }
};

#endif
