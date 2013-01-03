#ifndef D_BEHAVIOR_H
#define D_BEHAVIOR_H

class Behavior {
protected:
    int id;
public:
    virtual ~Behavior(){}

    virtual void sencing() = 0;
    virtual void perform() = 0;

    virtual const bool isActive() const = 0;

    const int getID() const { return id; }
};

#endif

