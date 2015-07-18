#ifndef COMMODITY_H
#define COMMODITY_H

class Gold;
class Commodity {
public:
    virtual bool eq(const Gold&) const = 0;
    virtual bool eq(const Commodity&) const { return false; }
    virtual bool operator==(const Commodity& c) const {
        return c.eq(*this);
    }
};

class Gold : public Commodity {
public:
    bool eq(const Gold&) const { return true; }
    bool operator==(const Commodity& c) const {
        return c.eq(*this);
    }
};

class Silver : public Commodity {
};

#endif
