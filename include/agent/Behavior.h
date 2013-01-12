#ifndef D_BEHAVIOR_H
#define D_BEHAVIOR_H

class Behavior {
protected:
    unsigned int id;
public:
    virtual ~Behavior(){}

    virtual void sensing() = 0;
    virtual void perform() = 0;

    virtual const bool isActive() const = 0;

    const unsigned int getID() const { return id; }
};

#endif

