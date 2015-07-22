#ifndef COMMODITY_H
#define COMMODITY_H

#include <iostream>
#include <typeinfo>

#include "include/SharedPtr.h"
#include "include/exceptions.h"

class Commodity;
typedef SharedPtr<Commodity> CommodityPtr;

CommodityPtr getCommodity(std::string name);

// An enum + global operator<< function would do for this
// exercise; however, in pursuing this design I got to play
// with multiple dispatch along the way (which proved to be
// unnecessary and was later removed).

class Commodity {
    virtual const char* getTag() const = 0;
public:
    virtual ~Commodity() {}

    virtual bool operator==(const Commodity& c) const {
        return typeid(*this) == typeid(c);
    }

    friend std::ostream& operator<<(std::ostream& o, 
                                    const Commodity& c) {
        return o << c.getTag();
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
