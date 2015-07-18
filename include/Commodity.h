#ifndef COMMODITY_H
#define COMMODITY_H

#include <iostream>

// An enum + global operator<< function would do for this
// exercise; however, in pursuing this design I got to play
// with multiple dispatch along the way (which proved to be
// unnecessary and was later removed).
// I leave this overkill version of Commodity because
// it is more *future proof*.

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
